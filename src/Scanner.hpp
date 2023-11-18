#include "Token.hpp"
#include "errorLog.hpp"
#include <string>
#include <vector>

class Scanner {
  std::string source;
  int start = 0;
  int current = 0;
  int line = 1;
  //  lox _lox;
  std::vector<Token> *tokens;

  bool isAtEnd();
  char advance();
  bool match(char excepted);
  char peek();
  char peekNext();
  void addToken(TokenType type);
  void addToken(TokenType type, std::string literal);
  void string_con();
  void number_con();
  void comment_con();
  bool isDigit(char c);

  bool isAlpha(char c);
  bool isAlphanumeric(char c);
  void identifier();

public:
  Scanner(std::string s);
  std::vector<Token> scanTokens();
  void scanToken();
  void scanToken(TokenType type, std::string literal);
};
