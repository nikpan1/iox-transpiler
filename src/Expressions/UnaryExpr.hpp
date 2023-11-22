#pragma once

#include <memory>

#include "Expr.hpp"
#include "Token.hpp"

class UnaryExpr : public Expr {
public:
  UnaryExpr(Token op, std::unique_ptr<Expr> right);

private:
  Token op;
  std::unique_ptr<Expr> right;
}
