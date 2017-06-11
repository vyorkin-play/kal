#ifndef __FUNCTION_NODE_H__
#define __FUNCTION_NODE_H__

#include "Base.hpp"
#include "Logger.hpp"
#include "ASTNode.hpp"
#include "PrototypeNode.hpp"

class FunctionNode: public ASTNode {
private:
  std::unique_ptr<PrototypeNode> proto;
  std::unique_ptr<ASTNode> body;
public:
  FunctionNode(std::unique_ptr<PrototypeNode> proto,
               std::unique_ptr<ASTNode> body):
    proto(std::move(proto)), body(std::move(body)) {}

  virtual llvm::Function* codegen() {
    llvm::Function* function = module->getFunction(proto->getName());
    if (!function) {
      function = proto->codegen();
    }
    if (!function) {
      return nullptr;
    }
    if (!function->empty()) {
      Logger::get().write("function cannot be redefined");
      return nullptr;
    }
    // create a new basic block to start insertion into
    llvm::BasicBlock* basicBlock = llvm::BasicBlock::Create(llvmContext, "entry", function);
    irBuilder.SetInsertPoint(basicBlock);
    // record the function arguments in the namedValues map
    namedValues.clear();
    for (auto &arg: function->args()) {
      namedValues[arg.getName()] = &arg;
    }
    if (llvm::Value* retValue = body->codegen()) {
      // finish off the function
      irBuilder.CreateRet(retValue);
      llvm::verifyFunction(*function);
      return function;
    }
    // error reading function body expression,
    // remove function
    function->eraseFromParent();
    return nullptr;
  }
};

#endif
