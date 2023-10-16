#include <array>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define endl '\n'
#define tab '\t'


std::array<std::string, 4> EXPRESSIONS = {
      "Binary   : Expr left, Token operator, Expr right",
      "Grouping : Expr expression",
      "Literal  : Object value",
      "Unary    : Token operator, Expr right"
};


bool isWhitespace(unsigned char c) {
    if (c == ' ' || c == '\t' || c == '\n' ||
        c == '\r' || c == '\f' || c == '\v') {
        return true;
    } else {
        return false;
    }
}


std::string eraseWS(std::string s) {
  s.erase(std::remove_if(s.begin(), s.end(), isWhitespace), s.end());
  return s;
}


std::vector<std::string> split(const std::string &str,
                               std::string separator) {
  std::vector<std::string> result;

  int start = 0, last = 0;
  int foundPos = str.find(separator);

  while (foundPos != std::string::npos) {
    result.push_back(str.substr(start, foundPos - start));
    start = foundPos + separator.size();

    foundPos = str.find(separator, start);
  }

  result.push_back(str.substr(start, str.length()));
  return result;
}

void defineType(std::ofstream &output, std::string &baseName,
                std::string &className, std::string &elements) {
  className = eraseWS(className);
  output << "static class " << className << " : " << baseName << " {\n";

  // constructor
  output << tab << "public:\n" << className << "(" << elements << ")";

  // store parameters in fields
  auto fields = split(elements, ", ");
  std::string initList = "\n";
  for (const auto field : fields) {
    initList += " " + field + ";\n";

    auto names = split(field, " ");
    auto name = names[1];
    output << " : " << name << '(' << name << ')';
  }
  output << "{}\n";
  className = eraseWS(className);

  // visitor interface
  output << initList;
  output << "\n template<typename R>" 
  "\n R accept(Visitor<R> visitor) {" 
  "\n\t return visitor.visit" 
  << className <<"Expr(this);\n}\n}\n";
}

template<typename T, size_t N>
void defineBase(std::ofstream& output, const std::array<T,N> &types) {
  // Expr class implementation
  output <<
  "\n class Expr {"
  "\n public:"
  "\n  template<typename R>"
  "\n  R accept(Visitor<R> visitor);"
  "\n };\n";

  // visitor class implementation
  output << "\n template<typename R>\n class Visitor{\n";
  for (const auto &type : types) {
    uint8_t semicol = type.find(':');
    std::string className = type.substr(0, semicol);
    className = eraseWS(className);
    output << tab << "R visit" << className << "Expr(" << className << " expr);\n";
  }

  output << "\n };\n";
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
  
  defineBase(output, types);
  output << "\n\n\n";

  for (const auto &type : types) {
    uint8_t semicol = type.find(':');
    std::string className = type.substr(0, semicol);
    std::string elements = type.substr(semicol + 1, type.length() - 1);
    std::cout << semicol << " " << className << elements;
    defineType(output, baseName, className, elements);
  }
  
  output << "\n";
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
