#ifndef __LEXER_H__
#define __LEXER_H__

#include <string>
#include <cctype>
#include <cstdio>
#include <cstdlib>

#include "Token.hpp"

class Lexer {
private:
  std::string identifier;
  double number;
public:
  int getToken();
};

#endif
