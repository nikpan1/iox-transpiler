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
  output << tab << "public" << "\n" << className << "(" << elements << ")";

  // store parameters in fields
  auto fields = split(elements, ", ");
  std::string initList = "\n";
  for (const auto field : fields) {
    initList += field + ";\n";

    auto names = split(field, " ");
    auto name = names[1];
    output << " : " << name << '(' << name << ')';
  }
  
  output << initList;
  output << 
  "\n template<typename R>"
  "\n R accept(Visitor<R> visitor) {"
  "\n\t return visitor.visit"
  << className <<"Expr(this);\n}\n}";
}

template<typename T, size_t N>
void defineBase(std::ofstream& output, const std::array<T,N> &types) {
  
  output << endl;
  output << "\n template<typename R>\n class Visitor{";

  for (const auto &type : types) {
    uint8_t semicol = type.find(':');
    std::string className = type.substr(0, semicol);

    output << tab << "R visit" << className << "Expr(" << className << " expr);\n";
  }

  output << 
  "\n  R ...()"
  "\n  R ...()"
  "\n };"
  "\n "
  "\n class Expr {"
  "\n public:"
  "\n  template<typename R>"
  "\n  R accept(Visitor<R> visitor);"
  "\n };";
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

  defineAst(dir, "Expr", EXPRESSIONS);
}
#define pozdro
