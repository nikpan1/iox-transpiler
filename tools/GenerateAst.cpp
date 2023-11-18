#include <array>
#include <cstddef>
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
    "Grouping : Expr expression", "Literal  : std::string value",
    "Unary    : Token operator, Expr right"};

std::vector<std::string> split(const std::string &str,
                               const std::string &separator) {
  std::vector<std::string> result;

  int start = 0, last = 0;
  int foundPos = str.find(separator);

  while (foundPos != std::string::npos) {
    result.push_back(str.substr(start, foundPos - start));
    start = foundPos + separator.size();

    foundPos = str.find(separator, start);
  }

  result.push_back(str.substr(start, str.length() - 1));
  return result;
}

void defineType(std::ofstream &output, std::string &baseName,
                std::string &className, std::string &elements) {
  output << "static class" << className << " : " << baseName << " {\n";

  // constructor
  output << tab << className << '(' << elements << ") {";

  // store parameters in fields
  auto fields = split(elements, ", ");
  for (const auto field : fields) {
    auto names = split(field, " ");
    auto name = names[1];
    output << " this." << name << " = " << name << ';';
  }
  output << "\t}\n";
  for (const auto field : fields) {
    output << "\t" << field << ';';
  }
  output << "\t}";
}

template <typename T, size_t N>
void defineType(std::ofstream output, std::string baseName,
                const std::array<T, N> &types) {}

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
  output << "#include <iostream>";
  output << endl;
  output << "class" + baseName + " {" + endl; // baseName to klasa bazowa
  for (const auto &type : types) {
    uint8_t semicol = type.find(':');
    std::string className = type.substr(0, semicol);
    std::string elements = type.substr(semicol + 1, type.length() - 1);
    std::cout << semicol << " " << className << elements;
    defineType(output, baseName, className, elements);
  }

  defineVisitor(output, baseName, types);

  output << "}" << endl;
  output.close();
}

#define EXPR int

class Visitor {
  std::string visitBinaryExpr(EXPR expr) {
    return parenthesize(expr.operator.lexeme, expr.left, expr.right);
  }
  std::string visitGroupingExpr(EXPR expr) {
    return parenthize("group", expr.expression);
  }
  std::string visitLiteralExpr(EXPR expr) {
    if (expr.value == "")
      return "nil";
    return expr.value.to_string();
  }
  std::string visitUnaryExpr(EXPR expr) {
    return parenthesize(expr.operator.lexeme, expr.right);
  }

  std::string parenthize(std::string name, std::vector<EXPR> exprs) {
    std::string result = "";
    result += ('(') + (name);
    for (const auto expr : exprs) {
      result += (' ');
      result += (expr.accept(this));
    }
    result += (')');

    return result;
  }
};

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "Usage: ./a.out directory\n";
    return -1;
  }
  std::string dir = argv[1];

  defineAst(dir, "Expr", EXPRESSIONS);
}
