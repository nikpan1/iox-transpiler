#include <array>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define endl '\n'
#define tab '\t'

std::array<std::string, 4> EXPRESSIONS = {
    "Binary   : Expr left, Token operator, Expr right",
    "Grouping : Expr expression", "Literal  : Object value",
    "Unary    : Token operator, Expr right"};

std::vector<std::string> split(const std::string &str,
                               const std::string &separator) {
  std::vector<std::string> result;

  int start = 0;
  int foundPos = str.find(separator);

  while (foundPos != std::string::npos) {
    result.push_back(str.substr(start, foundPos));
    start = foundPos + separator.size();
    foundPos = str.find(separator, foundPos + 1);
  }

  return result;
}

void defineType(std::ofstream &output, std::string &baseName,
                std::string &className, std::string &elements) {
  output << "static class" << className << " : " << baseName << " {\n";

  // constructor
  output << tab << className << '(' << elements << ") {";

  // store parameters in fields
  auto fields = split(elements, ", ");
}

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
  output << "class" + baseName + " {" + endl; // baseName to klasa bazowa
  for (const auto &type : types) {
    uint8_t semicol = type.find(':');
    std::string className = type.substr(0, semicol);
    std::string elements = type.substr(semicol + 1, type.length() - 1);
    std::cout << semicol << " " << className << elements;
    defineType(output, baseName, className, elements);
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

  std::string s = "test1, test2, test3, test4, 23rgrdg, o";
  auto p = split(s, ", ");
  for (const auto ps : p)
    std::cout << ps << "|" << endl;

  // defineAst(dir, "Expr", EXPRESSIONS);
}
