#ifndef __LEXER_H__
#define __LEXER_H__

#include "Base.hpp"
#include "Token.hpp"

class Lexer {
private:
  std::string identifier;
  double number;
  int token;
  int read();
public:
  std::string& getIdentifier();
  int getToken() const;
  double getNumber() const;
  int getNextToken();
};

#endif
