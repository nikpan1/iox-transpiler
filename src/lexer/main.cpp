#include <stdio.h>
#include <string>
public
class lox {
  static bool hadError = false;
} int main(int argc, char *argv[]) {
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
