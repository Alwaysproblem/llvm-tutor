#include "llvm/IR/Module.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/IR/IntrinsicInst.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"

#include "llvm/Transforms/Utils/BasicBlockUtils.h"

#include "llvm/ADT/Statistic.h"
#include "llvm/Support/Debug.h"

using namespace llvm;

bool canRemoveInst(const Instruction *Inst) {
  assert(Inst->hasOneUse() && "Inst needs to have exactly one use");

  auto *PNUse = dyn_cast<PHINode>(*Inst->user_begin());
  auto *Succ = Inst->getParent()->getTerminator()->getSuccessor(0);
  auto *User = cast<Instruction>(*Inst->user_begin());

  bool SameParentBB = (User->getParent() == Inst->getParent());
  bool UsedInPhi = (PNUse && PNUse->getParent() == Succ &&
                    PNUse->getIncomingValueForBlock(Inst->getParent()) == Inst);

  return UsedInPhi || SameParentBB;
}

int main(int argc, char **argv) {
  SMDiagnostic Err;
  LLVMContext Context;
  std::string IRFile = argv[1];
  raw_ostream &OS = outs();

  std::unique_ptr<Module> M = parseIRFile(IRFile, Err, Context);

  if (!M) {
    Err.print(argv[0], errs());
    return 1;
  }

  for (auto &F : *M) {
    for (auto &BB : F) {
      for (auto &I : BB) {
        auto *Inst = &I;
        if (Inst->hasOneUse()){
          auto *PNUse = dyn_cast<PHINode>(*Inst->user_begin());
          auto *Succ = Inst->getParent()->getTerminator()->getSuccessor(0);
          auto *User = cast<Instruction>(*Inst->user_begin());
          Succ->print(OS);

          bool SameParentBB = (User->getParent() == Inst->getParent());
          bool UsedInPhi = (PNUse && PNUse->getParent() == Succ &&
                            PNUse->getIncomingValueForBlock(Inst->getParent()) == Inst);
        }
      }
    }
  }

  return 0;
}