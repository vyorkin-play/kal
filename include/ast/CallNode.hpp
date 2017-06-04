#ifndef __CALL_NODE_H__
#define __CALL_NODE_H__

#include "Base.hpp"
#include "ASTNode.hpp"

class CallNode: public ASTNode {
private:
  std::string callee;
  std::vector<std::unique_ptr<ASTNode>> args;
public:
  CallNode(const std::string& callee,
           std::vector<std::unique_ptr<ASTNode>> args):
    callee(callee), args(std::move(args)) {}
};

#endif
