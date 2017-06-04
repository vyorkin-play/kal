#ifndef __VARIABLE_NODE_H__
#define __VARIABLE_NODE_H__

#include <string>
#include "ASTNode.hpp"

class VariableNode: public ASTNode {
private:
  std::string name;

public:
  VariableNode(const std::string& name): name(name) {}
};

#endif
