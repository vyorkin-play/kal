#include "Parser.hpp"

int Parser::getTokenPrecedence() const {
  const int token = lexer.getToken();
  if (!isascii(token)) {
    return -1;
  }
  const int precedence = precedenceMap.at(token);
  if (precedence <= 0) {
    return -1;
  }
  return precedence;
}

Parser::Parser(Lexer& lexer, Logger& logger):
  lexer(lexer), logger(logger) {
  precedenceMap['<'] = 10;
  precedenceMap['+'] = 20;
  precedenceMap['-'] = 20;
  precedenceMap['*'] = 40;
}

std::unique_ptr<ASTNode> Parser::parseNumber() {
  int currentNumber = lexer.getNumber();
  auto result = llvm::make_unique<NumberNode>(currentNumber);
  // consume the number
  lexer.getNextToken();
  return std::move(result);
}

std::unique_ptr<ASTNode> Parser::parseParenExpression() {
  lexer.getNextToken(); // eat (
  auto expression = parseExpression();
  if (!expression) {
    return nullptr;
  }
  if (lexer.getToken() != ')') {
    logger.write("expected )");
    return nullptr;
  }
  lexer.getNextToken(); // eat )
  return expression;
}

std::unique_ptr<ASTNode> Parser::parseIdentifier() {
  std::string identifierName = lexer.getIdentifier();
  lexer.getNextToken(); // eat identifier or (
  if (lexer.getToken() != '(') {
    // its just a variable
    return llvm::make_unique<VariableNode>(identifierName);
  }
  lexer.getNextToken(); // eat (
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
        logger.write("expected ')' or ',' in argument list");
        return nullptr;
      }
      lexer.getNextToken();
    }
  }
  // eat the )
  lexer.getNextToken();
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
      logger.write("unknown token when expecting an expression");
      return nullptr;
  }
}

std::unique_ptr<ASTNode> Parser::parseExpression() {
}

std::unique_ptr<ASTNode> Parser::parseBinaryRHS(const int precedence, std::unique_ptr<ASTNode>& lhs) {
}

std::unique_ptr<ASTNode> Parser::parsePrototype() {
}

std::unique_ptr<ASTNode> Parser::parseDefinition() {
}

std::unique_ptr<ASTNode> Parser::parseExtern() {
}
