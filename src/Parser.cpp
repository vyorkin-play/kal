#include "Parser.hpp"

Parser::Parser():
  lexer(Lexer()) {
}

Lexer& Parser::getLexer() {
  return lexer;
}

int Parser::getTokenPrecedence() const {
  const int token = lexer.getToken();
  if (precedenceMap.find(token) == std::end(precedenceMap))
		return -1;
	return precedenceMap.at(token);
}

std::unique_ptr<ASTNode> Parser::parseNumber() {
  int currentNumber = lexer.getNumber();
  auto result = llvm::make_unique<NumberNode>(currentNumber);
  lexer.readNextToken();
  return std::move(result);
}

std::unique_ptr<ASTNode> Parser::parseParenExpression() {
  lexer.readNextToken(); // eat (
  auto expression = parseExpression();
  if (!expression) {
    return nullptr;
  }
  if (lexer.getToken() != ')') {
    Logger::get().write("expected )");
    return nullptr;
  }
  lexer.readNextToken(); // eat )
  return expression;
}

std::unique_ptr<ASTNode> Parser::parseIdentifier() {
  std::string identifierName = lexer.getIdentifier();
  lexer.readNextToken(); // eat identifier or (
  if (lexer.getToken() != '(') {
    // its just a variable
    return llvm::make_unique<VariableNode>(identifierName);
  }
  // looks like a function call, lets try to read it
  lexer.readNextToken(); // eat (
  std::vector<std::unique_ptr<ASTNode>> args;
  if (lexer.getToken() != ')') {
    while (true) {
      auto arg = parseExpression();
      if (arg) {
        args.push_back(std::move(arg));
      } else {
        return nullptr;
      }
      if (lexer.getToken() == ')') {
        break;
      }
      if (lexer.getToken() != ',') {
        Logger::get().write("expected ')' or ',' in argument list");
        return nullptr;
      }
      lexer.readNextToken();
    }
  }
  // eat the )
  lexer.readNextToken();
  // its a function call
  return llvm::make_unique<CallNode>(identifierName, std::move(args));
}

std::unique_ptr<ASTNode> Parser::parsePrimary() {
  switch (lexer.getToken()) {
    case Token::Identifier:
      return parseIdentifier();
    case Token::Number:
      return parseNumber();
    case '(':
      return parseParenExpression();
    default:
      Logger::get().write("unknown token when expecting an expression");
      return nullptr;
  }
}

std::unique_ptr<ASTNode> Parser::parseExpression() {
  auto lhs = parsePrimary();
  return lhs ? parseBinaryRHS(0, std::move(lhs)) : nullptr;
}

// a + b + (c + d) * e * f + g
// a, [+, b] [+, (c+d)] [*, е] [*, f] [+, g]

std::unique_ptr<ASTNode> Parser::parseBinaryRHS(const int precedence, std::unique_ptr<ASTNode> lhs) {
  while (true) {
    int currentPrecedence = getTokenPrecedence();
    // if its either a higher precedence operator or
    // not an operator at all
    if (currentPrecedence < precedence) {
      return lhs;
    }
    // ok, its a binary operator for sure
    int binaryOp = lexer.getToken();
    lexer.readNextToken(); // eat it

    // parse the primary expression that
    // follows binary operator
    auto rhs = parsePrimary();
    if (!rhs) {
      return nullptr;
    }

    // next binary operator precedence
    int nextPrecedence = getTokenPrecedence();
    if (currentPrecedence < nextPrecedence) {
      rhs = parseBinaryRHS(currentPrecedence + 1, std::move(rhs));
      if (!rhs) {
        return nullptr;
      }
    }
    lhs = llvm::make_unique<BinaryNode>(binaryOp, std::move(lhs), std::move(rhs));
  }
}

std::unique_ptr<PrototypeNode> Parser::parsePrototype() {
  if (lexer.getToken() != Token::Identifier) {
    Logger::get().write("expected function name in prototype");
    return nullptr;
  }

  std::string functionName = lexer.getIdentifier();
  lexer.readNextToken(); // eat function name

  if (lexer.getToken() != '(') {
    Logger::get().write("expected '(' in prototype");
    return nullptr;
  }

  std::vector<std::string> args;
 // eat function arguments
  while (lexer.readNextToken() == Token::Identifier) {
    args.push_back(lexer.getIdentifier());
  }

  if (lexer.getToken() != ')') {
    Logger::get().write("expected ')' in prototype");
    return nullptr;
  }

  lexer.readNextToken(); // eat )

  return llvm::make_unique<PrototypeNode>(functionName, std::move(args));
}

std::unique_ptr<FunctionNode> Parser::parseDefinition() {
  lexer.readNextToken(); // eat def
  auto proto = parsePrototype();
  if (!proto) {
    return nullptr;
  }

  auto expression = parseExpression();
  return expression ?
    llvm::make_unique<FunctionNode>(std::move(proto), std::move(expression)) :
    nullptr;
}

std::unique_ptr<PrototypeNode> Parser::parseExtern() {
  lexer.readNextToken(); // eat extern
  return parsePrototype();
}

std::unique_ptr<FunctionNode> Parser::parseTopLevelExpression() {
  auto expression = parseExpression();
  if (!expression) {
    return nullptr;
  }
  // make an anonymous proto
  auto proto = llvm::make_unique<PrototypeNode>("__anon_expr", std::vector<std::string>());
  return llvm::make_unique<FunctionNode>(std::move(proto), std::move(expression));
}
