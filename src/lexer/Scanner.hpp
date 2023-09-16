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

public:
  Scanner(std::string s);
  std::vector<Token> scanTokens();
  void scanToken();
};
