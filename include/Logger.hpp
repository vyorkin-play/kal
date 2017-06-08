#ifndef __LOGGER_H__
#define __LOGGER_H__

#include "Base.hpp"

class Logger {
public:
  static Logger& get() {
    static Logger instance;
    return instance;
  }

  Logger(Logger const&) = delete;
  Logger(Logger&&) = delete;
  Logger& operator=(Logger const&) = delete;
  Logger& operator=(Logger&&) = delete;

  void write(const char* str);

protected:
  Logger();
};

#endif
