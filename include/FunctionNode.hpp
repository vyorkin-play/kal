#ifndef __FUNCTION_NODE_H__
#define __FUNCTION_NODE_H__

#include <memory>
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
};

#endif
