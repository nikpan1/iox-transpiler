#include <bits/types/FILE.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

#include "Core.cpp"
#define NULL (void *)0

void runFile(char *path);
void runPrompt();

class Token {

  TokenType type;
  std::string lexeme;
  Object literal;
  int line;

public:
  Token(TokenType tp, std::string le, Object lit, int lin) {
    type = tp;
    lexeme = le;
    literal = lit;
    line = lin;
  }
};

class Scanner {
  std::string source;
  char *current;
  std::vector<Token> tokens;

public:
  Scanner(std::string s) { source = s; }
  bool isAtEnd() { return *current >= source.length(); }

  std::vector<Token> scanTokens() {
    while (!isAtEnd()) {
      start = current;
      scanToken();
    }

    tokens.add(new Token(EOF, "", NULL, line));
    return tokens;
  }
};

int main(int argc, char *argv[]) {
  if (argc > 1) {
    printf("Usage: jlox [script]");
    return -1;
  } else if (argc == 1) {
    runFile(argv[0]);
  } else {
    runPrompt(); /* REPL - READ a line of input,
                  * EVALUATE it,
                  * PRINT ther result,
                  * LOOP and do it all over again
                  */
  }
}

class lox {
  bool hadError = false;

  void runPrompt() {
    std::string line;

    for (;;) {
      printf("> ");
      std::cout << line << std::endl;
      if (line.empty())
        break;
      run(line);
      line.clear();
    }
  }

  void run(std::string src) {
    Scanner scanner = new Scanner(src);
    std::vector<Token> tokens = scanner.scanTokens();

    for (Token token : tokens) {
      printf("%s", token);
    }
  }

  void error(int line, std::string message) { report(line, "", message); }

  void report(int line, std::string where, std::string message) {
    printf("[Line: %d] | Error: %s : \n->%s", line, message.c_str(),
           where.c_str());
  }
};
