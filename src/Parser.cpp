#include "Parser.hpp"

Parser::Parser(std::vector<Token> _tokens) {
  tokens = _tokens;
}

Expr Parser::expression() {
  return equality();
} 

Expr Parser::equality() {
  Expr result = comparision();
  while(match(BANG_EQUAL, EQUAL_EQUAL)) {
    Token operator = previous();
    Expr right = comparision();

    result = new Expr.Binary(expr, operator, right);
  }

  return expr;
}

bool Parser::match(std::vector<Token> types) {
  for(Token type : types) {
    if(check(type)) {
      advance();
      return true;
    }
  }
  return false;
}
