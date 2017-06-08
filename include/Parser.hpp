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

  std::map<char, int> precedenceMap {
    {'<', 10},
    {'+', 20},
    {'-', 20},
    {'*', 40},
  };

  int getTokenPrecedence() const;
public:
  Parser();

  Lexer& getLexer();

  // numberexpr ::= number
  std::unique_ptr<ASTNode> parseNumber();

  // parenexpr ::= '(' expression ')'
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

  // binaryrhs
  //   ::= (op primary)*
  std::unique_ptr<ASTNode> parseBinaryRHS(const int precedence, std::unique_ptr<ASTNode> lhs);

  // prototype
  //   ::= id '(' id* ')'
  std::unique_ptr<PrototypeNode> parsePrototype();

  // definition
  //   ::= 'def' prototype expression
  std::unique_ptr<FunctionNode> parseDefinition();

  // external
  //   ::= 'extern' prototype
  std::unique_ptr<PrototypeNode> parseExtern();

  // toplevelexpr
  //   ::= expression
  std::unique_ptr<FunctionNode> parseTopLevelExpression();
};

#endif
