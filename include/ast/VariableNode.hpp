#ifndef __VARIABLE_NODE_H__
#define __VARIABLE_NODE_H__

#include "Base.hpp"
#include "Logger.hpp"
#include "ASTNode.hpp"

class VariableNode: public ASTNode {
private:
  std::string name;

public:
  VariableNode(const std::string& name): name(name) {}

  virtual llvm::Value* codegen() {
    llvm::Value* value = namedValues[name];
    if (!value) {
      Logger::get().write("unknown variable name");
    }
    return value;
  }
};

#endif
