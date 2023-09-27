static class Binary    : Expr {
	public:
Binary   ( Expr left, Token operator, Expr right) : Expr(Expr) : operator(operator) : right(right){}

  Expr left;
 Token operator;
 Expr right;

 template<typename R>
 R accept(Visitor<R> visitor) {
	 return visitor.visitBinaryExpr(this);
}
}
static class Grouping  : Expr {
	public:
Grouping ( Expr expression) : Expr(Expr){}

  Expr expressio;

 template<typename R>
 R accept(Visitor<R> visitor) {
	 return visitor.visitGroupingExpr(this);
}
}
static class Literal   : Expr {
	public:
Literal  ( Object value) : Object(Object){}

  Object valu;

 template<typename R>
 R accept(Visitor<R> visitor) {
	 return visitor.visitLiteralExpr(this);
}
}
static class Unary     : Expr {
	public:
Unary    ( Token operator, Expr right) : Token(Token) : right(right){}

  Token operator;
 Expr right;

 template<typename R>
 R accept(Visitor<R> visitor) {
	 return visitor.visitUnaryExpr(this);
}
}
}
