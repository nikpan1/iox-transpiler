#include <bits/types/FILE.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

#include <fstream>
#include <sstream>

#include "Core.cpp"
#define NULL (void *)0

std::string readEntireFile(const std::string &filePath) {
  // @TODO check if the file path is correct depending on the OS
  std::ifstream inputFile(filePath);

  if (!inputFile.is_open()) {
    std::cerr << "Error: Could not open the file: " << filePath << std::endl;
    return "";
  }

  std::stringstream buffer;
  buffer << inputFile.rdbuf();
  inputFile.close();

  return buffer.str();
}

class lox {
  bool hadError = false;

  void runPrompt() {
    std::string input;
    for (;;) {
      printf("> ");
      std::getline(std::cin, input);

      if (input.empty())
        break;
      run(input);
      input.clear();
      hadError = false;
    }
  }

  void runFile(const std::string &path) {
    std::string source = readEntireFile(path);
    run(source);
  }

  void run(std::string src) {
    if (hadError) {
      std::cerr << "run | had an error.";
      // system.exit(-1);
    }

    Scanner scanner = new Scanner(src); // maybe into the constructor
    std::vector<Token> tokens = scanner.scanTokens();

    for (Token token : tokens) {
      printf("%s", token);
    }
  }

  static void error(int line, std::string message) {
    report(line, "", message);
  }

  static void report(int line, std::string where, std::string message) {
    printf("[Line: %d] | Error: %s : \n->%s", line, message.c_str(),
           where.c_str());
  }

public:
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
};
