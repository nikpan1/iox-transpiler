#include "errorLog.hpp"

void errorLog::error(int line, std::string message) {
  report(line, "", message);
}

void errorLog::report(int line, std::string where, std::string message) {
  printf("[Line: %d] | Error: %s : \n->%s", line, message.c_str(),
         where.c_str());
}
