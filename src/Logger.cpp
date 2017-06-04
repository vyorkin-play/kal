#include "Logger.hpp"

void Logger::write(const char *str) {
  std::cerr << "error: " << str << std::endl;
}
