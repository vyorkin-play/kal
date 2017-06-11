#include "Base.hpp"
#include "Lexer.hpp"
#include "Logger.hpp"
#include "Parser.hpp"

#include <unistd.h>
#include <signal.h>
#include <execinfo.h>

void handler(int sig) {
  void *array[10];
  size_t size;
  // get void*'s for all entries on the stack
  size = backtrace(array, 10);
  // print out all the frames to stderr
  std::cerr << "error: signal " << sig << std::endl;
  backtrace_symbols_fd(array, size, STDERR_FILENO);
  exit(1);
}

void processNode(const std::unique_ptr<ASTNode>& node, const char* text) {
  if (!node) return;
  if (auto *ir = node->codegen()) {
    std::cerr << text << std::endl;
    ir->print(llvm::errs());
    std::cerr << std::endl;
  }
}

void repl(Parser& parser) {
  while (true) {
    std::cerr << "> ";
    switch (parser.next()) {
    case Token::Eof:
      return;
    case ';':
      break;
    case Token::Def:
      processNode(parser.parseDefinition(), "function definition");
      break;
    case Token::Extern:
      processNode(parser.parseExtern(), "extern");
      break;
    default:
      processNode(parser.parseTopLevelExpression(), "top-level expression");
    }
  }
}

int main() {
  signal(SIGSEGV, handler);
  auto parser = Parser();
  repl(parser);
	return 0;
}
