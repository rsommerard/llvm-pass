#define DEBUG_TYPE "obfuscate"
#include <string.h>
#include "llvm/Pass.h"
#include "llvm/Type.h"
#include "llvm/Value.h"
#include "llvm/Constants.h"
#include "llvm/InstrTypes.h"
#include "llvm/BasicBlock.h"
#include "llvm/Instructions.h"
#include "llvm/Support/raw_ostream.h"
#include <ctime>

using namespace std;
using namespace llvm;

namespace {
  struct Obfuscate : public BasicBlockPass {
    static char ID;
    Obfuscate() : BasicBlockPass(ID) {}

    virtual bool runOnBasicBlock(BasicBlock &bb) {
      BasicBlock *pbb = &bb;
      
      // Iteration sur les BasicBlocks
      for (BasicBlock::iterator i = pbb->begin(), e = pbb->end(); i != e; ++i) {
        // Iteration sur les opérandes de l'Instruction
        for(unsigned int j=0; j < i->getNumOperands(); j++) {
            Value *operand = i->getOperand(j);
            
            // Test de caster en ConstantInt
            if (ConstantInt *cstint = dyn_cast<ConstantInt>(operand)) {
                
                if(cstint->getValue() != 0 && cstint->getValue() != 1)
                    continue;
            
                int rnd = rand();

                // Création de l'operande 1
                Value* ope1 = ConstantInt::get(operand->getType(), rnd);
                
                // Création de l'operande 2
                Value* ope2;
                
                // Si c'est 0, on remplace la valeur 0 par 42 - 42 
                if(cstint->getValue() == 0) {
                    ope2 = ConstantInt::get(operand->getType(), rnd);
                }
            
                // Si c'est 1, on remplace la valeur 1 par 42 - 41
                if(cstint->getValue() == 1) {
                    ope2 = ConstantInt::get(operand->getType(), rnd - 1);
                }
           
                // Création de l'opération de soustraction 
                Value* val = BinaryOperator::CreateSub(ope1, ope2, "tmp", i);
                i->replaceUsesOfWith(cstint, val);
            }
        }
      }
      return false;
    }
    
  };
}

char Obfuscate::ID = 0;
static RegisterPass<Obfuscate> X("obfuscate", "Obfuscate Pass", false, false);
