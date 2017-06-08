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

  virtual llvm::Value* codegen() {
    return nullptr;
  }
};

#endif
