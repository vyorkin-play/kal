#ifndef __BINARY_NODE_H__
#define __BINARY_NODE_H__

#include "ASTNode.hpp"

class NumberNode: public ASTNode {
private:
  double value;

public:
  NumberNode(double value): value(value) {}
};

#endif
