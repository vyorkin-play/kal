#include "Logger.hpp"

Logger::Logger() {}

void Logger::write(const char *str) {
  std::cerr << "error: " << str << std::endl;
}
