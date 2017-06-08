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
  double getNumber() const;
  int getToken() const;
  int readNextToken();
};

#endif
