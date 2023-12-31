#include "Token.hpp"

Token::Token(TokenType type, std::string lexeme, int line) {
  Token(type, lexeme, "", line);
}

Token::Token(TokenType type, std::string lexeme, std::string literal,
             int line) {
  type = type;
  lexeme = lexeme;
  literal = literal;
  line = line;
}

std::ostream &operator<<(std::ostream &os, const Token &obj) {
  os << obj.type << " " << obj.lexeme << "|" << obj.literal;
  return os;
}
