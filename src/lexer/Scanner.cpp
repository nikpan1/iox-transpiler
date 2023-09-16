#include "Scanner.hpp"

Scanner::Scanner(std::string s) { source = s; }
bool Scanner::isAtEnd() { return current >= source.length(); }

std::vector<Token> Scanner::scanTokens() {
  while (!isAtEnd()) {
    start = current;
    scanToken();
  }

  tokens.add(Token(EOF, "", NULL, line));
  return tokens;
}

void Scanner::scanToken() {
  char c = advance();
  switch (c) {
  case '(':
    addToken(LEFT_PAREN);
    break;
  case ')':
    addToken(RIGHT_PAREN);
    break;
  case '{':
    addToken(LEFT_BRACE);
    break;
  case '}':
    addToken(RIGHT_BRACE);
    break;
  case ',':
    addToken(COMMA);
    break;
  case '.':
    addToken(DOT);
    break;
  case '-':
    addToken(MINUS);
    break;
  case '+':
    addToken(PLUS);
    break;
  case ';':
    addToken(SEMICOLON);
    break;
  case '*':
    addToken(STAR);
    break;
  }
}

char Scanner::advance() { return source[current++]; }
void Scanner addToken(TokenType type, Object literal) { std::string }
void Scanner::addToken(TokenType type){addToken(type, NULL)};
