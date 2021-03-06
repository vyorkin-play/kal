#ifndef __PROTOTYPE_NODE_H__
#define __PROTOTYPE_NODE_H__

#include "Base.hpp"
#include "ASTNode.hpp"

class PrototypeNode: public ASTNode {
private:
  std::string name;
  std::vector<std::string> args;
public:
  PrototypeNode(const std::string& name,
                std::vector<std::string> args):
    name(name), args(args) {}

  const std::string& getName() const {
    return name;
  }

  virtual llvm::Function* codegen() {
    std::vector<llvm::Type*> doubles(args.size(), llvm::Type::getDoubleTy(llvmContext));
    llvm::FunctionType *functionType = llvm::FunctionType::get(llvm::Type::getDoubleTy(llvmContext), doubles, false);
    llvm::Function *function = llvm::Function::Create(functionType, llvm::Function::ExternalLinkage, name, module.get());

    unsigned int idx = 0;
    for (auto &arg: function->args()) {
      arg.setName(args[idx++]);
    }
    return function;
  }
};

#endif
