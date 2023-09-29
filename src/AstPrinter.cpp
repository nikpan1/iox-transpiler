#include "Core.cpp"
#include "Expr.cpp"
#include "Token.hpp"
#include "lox.cpp"
#include <string>

// @TODO remove this later
#define null NULL

class AstPrinter : Visitor<std::string> {
public:
  std::string print(Expr expr) { return expr.accept(this); }

private:
  template <typename... Args>
  std::string parenthesize(std::string name, Args... exprs) {
    std::string result;

    result = "(" + name;
    for (Expr expr : exprs) {
      result += " " + expr.accept(this);
    }
    result += ")";

    return result;
  }

public:
  std::string visitBinaryExpr(Binary expr) {
    return parenthesize(expr.operator.lexeme, expr.left, expr.right);
  }

  std::string visitGroupingExpr(Grouping expr) {
    return parenthesize("group", expr.expression);
  }

  std::string visitLiteralExpr(Literal expr) {
    if (expr.value == null)
      return "nil";
    return expr.value.toString();
  }

  std::string visitUnaryExpr(Unary expr) {
    return parenthesize(expr.operator.lexeme, expr.right);
  }
};

void main() {
  Expr expression =
      Binary(new Unary(new Token(MINUS, "-", void(0), 1), new Literal(123)),
             new Token(STAR, "*", null, 1), new Grouping(new Literal(45.67)));

  auto a = new AstPrinter();
  std::cout << a->print(expression);
  return 1;
}
