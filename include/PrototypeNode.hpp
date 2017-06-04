#ifndef __PROTOTYPE_NODE_H__
#define __PROTOTYPE_NODE_H__

#include <memory>
#include <vector>
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
};

#endif
