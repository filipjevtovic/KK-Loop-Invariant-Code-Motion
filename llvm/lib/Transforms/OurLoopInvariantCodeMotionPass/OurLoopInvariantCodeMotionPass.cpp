#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {
struct OurLoopInvariantCodeMotionPass : public FunctionPass {
  static char ID;
  OurLoopInvariantCodeMotionPass() : FunctionPass(ID) {}

  bool runOnFunction(Function &F) override { return false; }
};
} // namespace

char OurLoopInvariantCodeMotionPass::ID = 0;
static RegisterPass<OurLoopInvariantCodeMotionPass>
    X("our-licm-pass", "Simple Loop Invariant Code Motion Pass", false, false);
