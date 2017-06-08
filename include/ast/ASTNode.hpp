#ifndef __AST_NODE_H__
#define __AST_NODE_H__

#include "Base.hpp"

class ASTNode {
public:
  virtual ~ASTNode() {}
  virtual llvm::Value* codegen() = 0;
};

#endif
