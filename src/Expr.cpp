#include "Token.hpp"
#include "lox.cpp"
#include <any>

class Binary;
class Grouping;
class Literal;
class Unary;

template <typename R> class Visitor {
  R visitBinaryExpr(Binary expr);
  R visitGroupingExpr(Grouping expr);
  R visitLiteralExpr(Literal expr);
  R visitUnaryExpr(Unary expr);
};

class Expr {
public:
  template <typename R> R accept(Visitor<R> visitor);
};

static class Binary : Expr {
public:
  Binary(Expr _left, Token _operator, Expr _right)
      : Expr(_left), operator(_operator), right(_right) {}

  Expr left;
  Token operator;
  Expr right;

  template <typename R> R accept(Visitor<R> visitor) {
    return visitor.visitBinaryExpr(this);
  }
} static class Grouping : Expr {
public:
  Grouping(Expr expression) : Expr(expression) {}

  Expr expression;

  template <typename R> R accept(Visitor<R> visitor) {
    return visitor.visitGroupingExpr(this);
  }
} static class Literal : Expr {
public:
  Literal(std::any value) : value(value) {}

  std::value value;

  template <typename R> R accept(Visitor<R> visitor) {
    return visitor.visitLiteralExpr(this);
  }
} static class Unary : Expr {
public:
  Unary(Token operator, Expr right) : Token(Token) : right(right) {}

  Token operator;
  Expr right;

  template <typename R> R accept(Visitor<R> visitor) {
    return visitor.visitUnaryExpr(this);
  }
}
}
