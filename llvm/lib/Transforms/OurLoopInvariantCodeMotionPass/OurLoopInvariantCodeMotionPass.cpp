#include "llvm/Analysis/LoopPass.h"
#include "llvm/Pass.h"

using namespace llvm;

namespace {
// Prebacio sam sablon sa FunctionPass na LoopPass.
struct OurLoopInvariantCodeMotionPass : public LoopPass {
  static char ID;
  OurLoopInvariantCodeMotionPass() : LoopPass(ID) {}

  bool runOnLoop(Loop *CurrentLoop, LPPassManager &LoopPassManager) override {
    return false;
  }
};
} // namespace

char OurLoopInvariantCodeMotionPass::ID = 0;
static RegisterPass<OurLoopInvariantCodeMotionPass>
    X("our-licm-pass", "Simple Loop Invariant Code Motion Pass", false, false);
