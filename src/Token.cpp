#include "Token.hpp"

Token::Token(TokenType tp, std::string le, Object lit, int lin) {
  type = tp;
  lexeme = le;
  literal = lit;
  line = lin;
}

std::ostream &operator<<(std::ostream &os, const Token &obj) {
  os << obj.type << " " << obj.lexeme << "|" << obj.literal;
  return os;
}
