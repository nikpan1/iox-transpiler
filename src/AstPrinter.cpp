#include "Expr.cpp"
#include "Token.hpp"
#include "lox.cpp"
#include <string>

class AstPrinter : Visitor<std::string> {
public:
  std::string print(Expr expr) { return expr.accept(this); }

private:
  template <typename... Args>
  std::string parenthesize(std::string name, Args... exprs) {
    std::string result;

    result = "(" + name;
    for (Expr expr : exprs) {
      result += " ";
      result += expr.accept(this);
    }
    result += ")";

    return result;
  }

public:
  std::string visitBinaryExpr(Binary expr) {
    return parenthesize(operator.lexeme, left, right);
  }

  std::string visitGroupingExpr(Grouping expr) {
    return parenthesize("group", expression);
  }

  std::string visitLiteralExpr(Literal expr) {
    if (value == null)
      return "nil";
    return value.toString();
  }

  std::string visitUnaryExpr(Unary expr) {
    return parenthesize(operator.lexeme, right);
  }
};

void main() {
  Expr expression = Binary(
      new Unary(new Token(TokenType.MINUS, "-", null, 1), new Literal(123)),
      new Token(TokenType.STAR, "*", null, 1),
      new Grouping(new Literal(45.67)));

  auto a = new AstPrinter();
  std::cout << a->print(expression);
}
