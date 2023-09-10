#include <stdio.h>
#include <string>
#include <vector>

enum TokenType {
  // Single-character tokens.
  LEFT_PAREN,
  RIGHT_PAREN,
  LEFT_BRACE,
  RIGHT_BRACE,
  COMMA,
  DOT,
  MINUS,
  PLUS,
  SEMICOLON,
  SLASH,
  STAR,

  // One or two character tokens.
  BANG,
  BANG_EQUAL,
  EQUAL,
  EQUAL_EQUAL,
  GREATER,
  GREATER_EQUAL,
  LESS,
  LESS_EQUAL,

  // Literals.
  IDENTIFIER,
  STRING,
  NUMBER,

  // Keywords.
  AND,
  CLASS,
  ELSE,
  FALSE,
  FUN,
  FOR,
  IF,
  NIL,
  OR,
  PRINT,
  RETURN,
  SUPER,
  THIS,
  TRUE,
  VAR,
  WHILE,

  EOF
};

class Token {

  TokenType type;
  std::string lexeme;
  Object literal;
  int line;

  Token(TokenType tp, std::string le, Object lit, int lin) {
    type = tp;
    lexeme = le;
    literal = lit;
    line = lin;
  }
  bool isAtEnd() { return current >= source.length(); }
  std::vector<Token> scanTokens() {
    while (!isAtEnd()) {
      start = current;
      scanToken();
    }

    tokens.add(new Token(EOF, "", null, line));
    return tokens;
  }
}

class Scanner {
  std::string src;
  std::vector<Token> tokens;

  Scanner(std::string s) { src = s; }
}

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
      scanf("%s", line.c_str());
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
      printf("%s", token)
    }
  }

  void error(int line, std::string message) { report(line, "", message); }

  void report(int line, std::string where, std::string message) {
    printf("[Line: %d] | Error: %s : \n->%s", line, message.c_str(),
           where.c_str());
  }
}
