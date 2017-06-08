#include "Base.hpp"
#include "Lexer.hpp"
#include "Logger.hpp"
#include "Parser.hpp"

// playground

void repl(Parser& parser) {
  auto lexer = parser.getLexer();
  while (true) {
    std::cerr << "> ";
    lexer.readNextToken();
    switch (lexer.getToken()) {
    case Token::Eof:
      return;
    case ';':
      break;
    case Token::Def:
      if (parser.parseDefinition()) {
        std::cerr << "function definition" << std::endl;
      }
      break;
    case Token::Extern:
      if (parser.parseExtern()) {
        std::cerr << "extern" << std::endl;
      }
      break;
    default:
      if (parser.parseTopLevelExpression()) {
        std::cerr << "top-level expression" << std::endl;
      }
    }
  }
}

int main() {
  auto parser = Parser();
  repl(parser);
	return 0;
}
