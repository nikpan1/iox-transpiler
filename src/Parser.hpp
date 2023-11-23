#include "Token.hpp"
#include <vector>
#include "Expr.hpp"

class Parser {
private:
  std::vector<Token> tokens;
  int current = 0;

public:
  Parser(std::vector<Token> _tokens);

public:
  Expr expression(); 
  Expr equality();

  bool match(std::vector<Token> tokens); 
}
