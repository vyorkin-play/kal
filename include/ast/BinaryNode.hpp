#ifndef __BINARY_NODE_H__
#define __BINARY_NODE_H__

#include "Base.hpp"
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
};

#endif
