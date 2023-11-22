#pragma once

#include <memory>

#include "Expr.hpp"
#include "Token.hpp"

class BinaryExpr : public Expr {
public:
  BinaryExpr(std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right);

private:
  std::unique_ptr<Expr> left;

  Token op;
  std::unique_ptr<Expr> right;
}
