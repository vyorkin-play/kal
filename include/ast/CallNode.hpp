#ifndef __CALL_NODE_H__
#define __CALL_NODE_H__

#include "Base.hpp"
#include "Logger.hpp"
#include "ASTNode.hpp"

class CallNode: public ASTNode {
private:
  std::string callee;
  std::vector<std::unique_ptr<ASTNode>> args;
public:
  CallNode(const std::string& callee,
           std::vector<std::unique_ptr<ASTNode>> args):
    callee(callee), args(std::move(args)) {}

  virtual llvm::Value* codegen() {
    llvm::Function *func = module->getFunction(callee);
    if (!func) {
      Logger::get().write("unknown function referenced");
      return nullptr;
    }
    if (func->arg_size() != args.size()) {
      Logger::get().write("incorrect number of arguments passed");
      return nullptr;
    }
    std::vector<llvm::Value*> argsv;
    for (unsigned int i = 0, count = args.size(); i != count; ++i) {
      argsv.push_back(args[i]->codegen());
      if (!argsv.back()) {
        return nullptr;
      }
    }
    return irBuilder.CreateCall(func, argsv, "calltmp");
  }
};

#endif
