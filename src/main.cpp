#include "Base.hpp"
#include "Lexer.hpp"
#include "Logger.hpp"
#include "Parser.hpp"

int main() {
  Logger logger;
  Lexer lexer;
  Parser parser = Parser(lexer, logger);
	return 0;
}
