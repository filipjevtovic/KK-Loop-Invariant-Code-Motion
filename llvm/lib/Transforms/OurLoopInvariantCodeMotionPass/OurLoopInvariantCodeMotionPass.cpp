#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/LoopPass.h"
#include "llvm/Pass.h"

#include "llvm/Support/raw_ostream.h"

#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"

#include "LoopInvariantAnalysis.h"
#include <vector>

using namespace llvm;

namespace {
// Prebacio sam sablon sa FunctionPass na LoopPass.
struct OurLoopInvariantCodeMotionPass : public LoopPass {
  static char ID;
  OurLoopInvariantCodeMotionPass() : LoopPass(ID) {}

  bool runOnLoop(Loop *CurrentLoop, LPPassManager &LoopPassManager) override {
    bool IRChanged = false;
    errs() << "OUR LICM PASS IS RUNNING!\n";

    BasicBlock *Preheader = CurrentLoop->getLoopPreheader();
    // Za sada cu izbegavati petlje bez preheader-a
    if (!Preheader)
      return false;

    LoopInvariantAnalysis Analysis;
    std::vector<Instruction *> Invariants =
        Analysis.findInvariantInstructions(*CurrentLoop);

    for (auto I : Invariants) {
      errs() << "Invariant: " << I << "\n";
    }

    for (Instruction *I : Invariants) {
      IRChanged = true;
      I->moveBefore(Preheader->getTerminator());
    }

    return IRChanged && !Invariants.empty();
  }
};
} // namespace

char OurLoopInvariantCodeMotionPass::ID = 0;
static RegisterPass<OurLoopInvariantCodeMotionPass>
    X("our-licm-pass", "Simple Loop Invariant Code Motion Pass", false, false);
