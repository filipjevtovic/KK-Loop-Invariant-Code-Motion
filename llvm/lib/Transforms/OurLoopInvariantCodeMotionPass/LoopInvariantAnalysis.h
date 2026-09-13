#ifndef LLVM_TRANSFORMS_OURLOOPINVARIANTCODEMOTIONPASS_LOOPINVARIANTANALYSIS_H
#define LLVM_TRANSFORMS_OURLOOPINVARIANTCODEMOTIONPASS_LOOPINVARIANTANALYSIS_H

#include <vector>

namespace llvm {
class BasicBlock;
class Instruction;
class Loop;
class Value;
} // namespace llvm

class LoopInvariantAnalysis {
public:
  // redosled u vektoru garantuje da je definicija pre instrukcija koje je
  // koriste, mozes ih tim redom premestiti bez dodatnog sortiranja
  std::vector<llvm::Instruction *>
  findInvariantInstructions(llvm::Loop &CurrentLoop) const;

private:
  bool isSupportedInstruction(const llvm::Instruction &Instruction) const;

  bool isInvariantOperand(
      const llvm::Value &Operand, const llvm::Loop &CurrentLoop,
      const std::vector<llvm::Instruction *> &InvariantInstructions) const;

  bool isInsideSubLoop(const llvm::BasicBlock &Block,
                       const llvm::Loop &CurrentLoop) const;
};

#endif
