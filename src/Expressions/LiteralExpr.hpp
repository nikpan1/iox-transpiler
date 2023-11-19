#pragma once

#include "Expr.hpp"
#include "Token.hpp"
#include <any>

class LiteralExpr : public Expr {
public:
  LiteralExpr(std::any literal);

private:
  std::any literal;
};
