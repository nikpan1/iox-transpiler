#include <iostream>
#include <vector>

class errorLog {
public:
  static void error(int line, std::string message);
  static void report(int line, std::string where, std::string message);
};
