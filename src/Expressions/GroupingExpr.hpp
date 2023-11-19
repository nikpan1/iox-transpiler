#pragma once

#include <memory>

#include "Expr.hpp"
#include "Token.hpp"

class GroupingExpr : public Expr {
public:
  GroupingExpr(std::unique_ptr<Expr> expr);

private:
  std::unique_ptr<Expr> expr;
};
