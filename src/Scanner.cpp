#include "Scanner.hpp"

Scanner::Scanner(std::string _source) {
  source = _source;
  tokens = new std::vector<Token>();
}
bool Scanner::isAtEnd() { return current >= source.length(); }

std::vector<Token> Scanner::scanTokens() {
  while (!isAtEnd()) {
    start = current;
    scanToken();
  }

  // @TODO is it right?
  tokens->push_back(Token(ENDOF, "", "", line));
  return *tokens;
}

void Scanner::scanToken() {
  char c = advance();
  switch (c) {
  case '(':
    addToken(LEFT_PAREN);
    break;
  case ')':
    addToken(RIGHT_PAREN);
    break;
  case '{':
    addToken(LEFT_BRACE);
    break;
  case '}':
    addToken(RIGHT_BRACE);
    break;
  case ',':
    addToken(COMMA);
    break;
  case '.':
    addToken(DOT);
    break;
  case '-':
    addToken(MINUS);
    break;
  case '+':
    addToken(PLUS);
    break;
  case ';':
    addToken(SEMICOLON);
    break;
  case '*':
    addToken(STAR);
    break;
  case '!':
    addToken(match('=') ? BANG_EQUAL : BANG);
    break;
  case '=':
    addToken(match('=') ? EQUAL_EQUAL : EQUAL);
    break;
  case '<':
    addToken(match('=') ? LESS_EQUAL : LESS);
    break;
  case '>':
    addToken(match('=') ? GREATER_EQUAL : GREATER);
    break;
  case '/':
    if (match('/')) {
      if (peek() == '*') // comment block
        comment_con();
      // A comment goes until the end of the line.
      while (peek() != '\n' && !isAtEnd())
        advance();
    } else {
      addToken(SLASH);
    }
    break;

  case ' ':
  case '\r':
  case '\t':
    // Ignore whitespace.
    break;

  case '\n':
    line++;
    break;
  case '"':
    string_con();
    break;
  default:
    if (isDigit(c)) {
      number_con();
    } else if (isAlpha(c)) {
      identifier();
    } else {

      errorLog::error(line, "Unexpected character.");
    }
    break;
  }
}

char Scanner::advance() { return source[current++]; }
void Scanner::addToken(TokenType type, std::string literal) {
  std::string text = source.substr(start, current);
  tokens->push_back(Token(type, text, literal, line));
}

void Scanner::addToken(TokenType type) { addToken(type, ""); }

bool Scanner::match(char excepted) {
  if (isAtEnd() || source[current] != excepted)
    return false;
  current++;
  return true;
}

char Scanner::peek() {
  if (isAtEnd())
    return '\0';
  return source[current];
}

void Scanner::string_con() {
  while (peek() != '"' && !isAtEnd()) {
    if (peek() == '\n')
      line++;
    advance();
  }

  if (isAtEnd()) {
    errorLog::error(line, "Unterminated string.");
    return;
  }

  advance(); // closing ""

  std::string value = source.substr(start + 1, current - 1);
  addToken(STRING, value);
}

bool Scanner::isDigit(char c) { return (c >= '0' && c <= '9'); }

void Scanner::number_con() {
  while (isDigit(peek()))
    advance();
  if (peek() == '.' && isDigit(peekNext())) {
    // consumes the '.'
    advance();
    while (isDigit(peek()))
      advance();
  }
  double strNumToDouble = std::stod(source.substr(start, current));
  addToken(NUMBER, std::to_string(strNumToDouble));
}

void Scanner::comment_con() {
  advance();
  while (peek() != '*') {
    if (peek() == '\n')
      line++;
    if (peek() == '/')
      if (peek() == '*')
        comment_con();
  }
  advance();
}

char Scanner::peekNext() {
  if (current + 1 >= source.length())
    return '\0';
  return source[current + 1];
}

void Scanner::identifier() {
  while (isAlphanumeric(peek()))
    advance();

  std::string text = source.substr(start, current);
  TokenType type = keywords.find(text)->second;
  // if (!type)
  //     type = IDENTIFIER;
  addToken(IDENTIFIER);
}

bool Scanner::isAlpha(char c) {
  return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_'));
}

bool Scanner::isAlphanumeric(char c) { return isAlpha(c) || isDigit(c); }
