#include "LoopInvariantAnalysis.h"

#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/ValueTracking.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"

#include <algorithm>

using namespace llvm;

std::vector<Instruction *>
LoopInvariantAnalysis::findInvariantInstructions(Loop &CurrentLoop) const {
  std::vector<Instruction *> InvariantInstructions;
  std::vector<BasicBlock *> BlocksToAnalyze;
  BasicBlock *Preheader = CurrentLoop.getLoopPreheader();

  // analiziramo samo basic blockove koji direktno pripadaju ovoj petlji,
  // svaki subloop ce LoopPass obraditi zasebno, pa ne proveravamo iste
  // instrukcije vise puta
  for (BasicBlock *Block : CurrentLoop.getBlocks()) {
    if (!isInsideSubLoop(*Block, CurrentLoop))
      BlocksToAnalyze.push_back(Block);
  }

  // ponavljamo analizu do fiksne tacke, jer novootkrivena invarijantna
  // instrukcija moze uciniti invarijantnim instrukcije koje je koriste
  bool FoundNewInvariant;
  do {
    FoundNewInvariant = false;

    for (BasicBlock *Block : BlocksToAnalyze) {
      for (Instruction &Instruction : *Block) {
        // za sada podrzavamo osnovnu aritmetiku bez deljenja, bitovske and/or
        // operacije i celobrojno poredjenje
        if (!isSupportedInstruction(Instruction))
          continue;

        if (auto LoadInstruction = dyn_cast<LoadInst>(&Instruction)) {
          if (!isLoadInstructionInvariant(LoadInstruction, CurrentLoop))
            continue;
        }

        // vec pronadjene invarijantne instrukcije ne proveravamo ponovo.
        if (std::find(InvariantInstructions.begin(),
                      InvariantInstructions.end(),
                      &Instruction) != InvariantInstructions.end())
          continue;

        // ako su svi operandi invarijantni, instrukcija je invarijantna
        bool AllOperandsAreInvariant =
            std::all_of(Instruction.op_begin(), Instruction.op_end(),
                        [&](const Use &Operand) {
                          return isInvariantOperand(*Operand.get(), CurrentLoop,
                                                    InvariantInstructions);
                        });

        if (!AllOperandsAreInvariant)
          continue;

        // pomeranje u preheader moze izvrsiti instrukciju koja se originalno
        // nije izvrsavala, na primer zbog grane ili petlje sa nula iteracija,
        // ovo je problematicno za deljenje kod kog je delilac nula, neispravan
        // load ili poziv funkcije sa bocnim efektima
        // ovo je trenutno overkill al ostavljam ako prosirimo, svakako je
        // kul za ispricati na odbrani a garantuje validnost
        if (!isSafeToSpeculativelyExecute(&Instruction,
                                          Preheader->getTerminator()))
          continue;

        InvariantInstructions.push_back(&Instruction);
        FoundNewInvariant = true;
      }
    }
  } while (FoundNewInvariant);

  return InvariantInstructions;
}

bool LoopInvariantAnalysis::isSupportedInstruction(
    const Instruction &Instruction) const {
  switch (Instruction.getOpcode()) {
  case Instruction::Add:
  case Instruction::Sub:
  case Instruction::Mul:
  case Instruction::And:
  case Instruction::Or:
  case Instruction::ICmp:
  case Instruction::Load:
    return true;
  default:
    return false;
  }
}

bool LoopInvariantAnalysis::isInvariantOperand(
    const Value &Operand, const Loop &CurrentLoop,
    const std::vector<Instruction *> &InvariantInstructions) const {
  // isLoopInvariant vraca true za vrednosti definisane van petlje, kao i za
  // globale, argumente funkcije i konstante, vraca false za instrukcije koje su
  // jos unutar petlje a one mogu ipak biti logicki invarijantne, pa njih
  // trazimo u nasem vektoru
  if (CurrentLoop.isLoopInvariant(&Operand))
    return true;

  // ako je palo proslu proveru, znamo da je operand instrukcija unutar petlje.
  const Instruction *OperandInstruction = cast<Instruction>(&Operand);

  return std::find(InvariantInstructions.begin(), InvariantInstructions.end(),
                   OperandInstruction) != InvariantInstructions.end();
}

bool LoopInvariantAnalysis::isInsideSubLoop(const BasicBlock &Block,
                                            const Loop &CurrentLoop) const {
  return std::any_of(
      CurrentLoop.getSubLoops().begin(), CurrentLoop.getSubLoops().end(),
      [&](const llvm::Loop *SubLoop) { return SubLoop->contains(&Block); });
}

bool LoopInvariantAnalysis::isLoadInstructionInvariant(
    llvm::LoadInst *LoadInst, llvm::Loop &CurrentLoop) const {
  Value *Operand = LoadInst->getOperand(0);

  if (!CurrentLoop.isLoopInvariant(Operand))
    return false;

  // Da bi store bio invarijantan, mora da se nista ne upisuje u taj operand u
  // petlji...
  for (BasicBlock *BB : CurrentLoop.getBlocks()) {
    for (Instruction &I : *BB) {
      if (auto StoreInstruction = dyn_cast<StoreInst>(&I)) {
        Value *StoreOperand = StoreInstruction->getOperand(1);
        if (StoreOperand == Operand)
          return false;
      }
    }
  }

  return true;
}
