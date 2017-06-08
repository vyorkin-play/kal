#ifndef __BINARY_NODE_H__
#define __BINARY_NODE_H__

#include "Base.hpp"
#include "Logger.hpp"
#include "ASTNode.hpp"

class BinaryNode: public ASTNode {
private:
  char op;
  std::unique_ptr<ASTNode> lhs;
  std::unique_ptr<ASTNode> rhs;
public:
  BinaryNode(const char op,
             std::unique_ptr<ASTNode> lhs,
             std::unique_ptr<ASTNode> rhs):
    op(op), lhs(std::move(lhs)), rhs(std::move(rhs)) {}

  virtual llvm::Value* codegen() {
    llvm::Value* l = lhs->codegen();
    llvm::Value* r = rhs->codegen();
    if (!(l && r)) {
      return nullptr;
    }

    switch (op) {
    case '+':
      return irBuilder.CreateFAdd(l, r, "addtmp");
    case '-':
      return irBuilder.CreateFSub(l, r, "subtmp");
    case '*':
      return irBuilder.CreateFMul(l, r, "multmp");
    case '<':
      l = irBuilder.CreateFCmpULT(l, r, "cmptmp");
      return irBuilder.CreateUIToFP(l, llvm::Type::getDoubleTy(llvmContext), "booltmp");
    default:
      Logger::get().write("invalid binary operator");
      return nullptr;
    }
  }
};

#endif
