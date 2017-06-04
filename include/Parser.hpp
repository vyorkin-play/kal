#ifndef __PARSER_H__
#define __PARSER_H__

#include "Base.hpp"
#include "Token.hpp"
#include "Lexer.hpp"
#include "Logger.hpp"

#include "ast/ASTNode.hpp"
#include "ast/VariableNode.hpp"
#include "ast/BinaryNode.hpp"
#include "ast/CallNode.hpp"
#include "ast/FunctionNode.hpp"
#include "ast/NumberNode.hpp"
#include "ast/PrototypeNode.hpp"

class Parser {
private:
  Lexer lexer;
  Logger logger;
  std::map<char, int> precedenceMap;

  int getTokenPrecedence() const;
public:
  Parser(Lexer& lexer, Logger& logger);
  // numberexpr ::= number
  std::unique_ptr<ASTNode> parseNumber();
  // parentexpr ::= '(' expression ')'
  std::unique_ptr<ASTNode> parseParenExpression();
  // identifierexpr
  //   ::= identifier
  //   ::= identifier '(' expression* ')'
  std::unique_ptr<ASTNode> parseIdentifier();
  // primary
  //   ::= identifierexpr
  //   ::= numberexpr
  //   ::= parenexpr
  std::unique_ptr<ASTNode> parsePrimary();
  // expression
  //   ::= primary binaryrhs
  std::unique_ptr<ASTNode> parseExpression();
  std::unique_ptr<ASTNode> parseBinaryRHS(const int precedence, std::unique_ptr<ASTNode>& lhs);
  std::unique_ptr<ASTNode> parsePrototype();
  std::unique_ptr<ASTNode> parseDefinition();
  std::unique_ptr<ASTNode> parseExtern();
};

#endif
