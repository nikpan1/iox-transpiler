#include "Core.cpp"
#include "Token.hpp"
#include <string>
#include <vector>

class Scanner {
  std::string source;
  int start = 0;
  int current = 0;
  int line = 1;

  std::vector<Token> tokens;

  bool isAtEnd();
  char advance();
  bool match(char excepted);
  char peek();
  void addToken(TokenType type);
  void addToken(TokenType type, Object literal);

public:
  Scanner(std::string s);
  std::vector<Token> scanTokens();
  void scanToken();
  void scanToken(TokenType type, Object literal);
};
