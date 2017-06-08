#ifndef __NUMBER_NODE_H__
#define __NUMBER_NODE_H__

#include "Base.hpp"
#include "ASTNode.hpp"

class NumberNode: public ASTNode {
private:
  double value;

public:
  NumberNode(double value): value(value) {}

  virtual llvm::Value* codegen() {
    return llvm::ConstantFP::get(llvmContext, llvm::APFloat(value));
  }
};

#endif
