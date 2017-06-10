#include "Token.hpp"
#include "Lexer.hpp"

int Lexer::read() {
  static int lastChar = ' ';

  while (isspace(lastChar)) {
    lastChar = getchar();
  }

  if (isalpha(lastChar)) {
    identifier = lastChar;

    while (isalnum(lastChar = getchar())) {
      identifier += lastChar;
    }

    if (identifier == "def") {
      return Token::Def;
    }

    if (identifier == "extern") {
      return Token::Extern;
    }

    return Token::Identifier;
  }

  // TODO: it will incorrectly read "1.23.45.67" and
  // handle it as if you typed in "1.23"
  if (isdigit(lastChar) || lastChar == '.') {
    std::string numberStr;

    do {
      numberStr += lastChar;
      lastChar = getchar();
    } while (isdigit(lastChar) || lastChar == '.');

    number = strtod(numberStr.c_str(), 0);
    return Token::Number;
  }

  if (lastChar == '#') {
    do {
      lastChar = getchar();
    } while (lastChar != EOF && lastChar != '\n' && lastChar != '\r');

    if (lastChar != EOF) {
      return read();
    }
  }

  // if the input doesn't match one of the above cases
  // it's either an operator character like '+', '*' and '>' or the end of the file
  if (lastChar == EOF) {
    return Token::Eof;
  }

  int currentChar = lastChar;
  lastChar = std::getchar();
  return currentChar;
}

std::string& Lexer::getIdentifier() {
  return identifier;
}

int Lexer::getToken() const {
  return token;
}

double Lexer::getNumber() const {
  return number;
}

int Lexer::readNextToken() {
  token = read();
  return token;
}
