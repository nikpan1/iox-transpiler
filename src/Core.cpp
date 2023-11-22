#include <map>
#include <string>

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
  FUNCTION,
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
  ENDOF // EOF
};

std::map<std::string, TokenType> keywords = {
    {"AND", AND},     {"OR", OR},       {"class", CLASS},   {"else", ELSE},
    {"False", FALSE}, {"for", FOR},     {"def", FUNCTION},  {"if", IF},
    {"nil", NIL},     {"print", PRINT}, {"return", RETURN}, {"super", SUPER},
    {"this", THIS},   {"True", TRUE},   {"var", VAR},       {"while", WHILE}};
