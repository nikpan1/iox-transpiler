#include <array>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#define endl '\n'

std::array<std::string, 4> EXPRESSIONS = {
    "Binary   : Expr left, Token operator, Expr right",
    "Grouping : Expr expression", "Literal  : Object value",
    "Unary    : Token operator, Expr right"};

template <typename T, size_t N>
void defineAst(std::string outputDir, std::string baseName,
               const std::array<T, N> &types) {
  std::string path = outputDir + "/" + baseName + ".cpp";
  std::ofstream output;
  output.open(path);

  if (!output.is_open()) {
    std::cerr << "Failed to open the file. | defineAst\n";
    exit(-1);
  }

  output << endl;
  output << "class" + baseName + " {" + endl;
  for (const auto &type : types) {
  }

  output << "}" << endl;
  output.close();
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "Usage: ./a.out directory\n";
    return -1;
  }
  std::string dir = argv[1];
  defineAst(dir, "Expr", EXPRESSIONS);
}
