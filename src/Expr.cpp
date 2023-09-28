
 class Expr {
 public:
  template<typename R>
  R accept(Visitor<R> visitor);
 };

 template<typename R>
 class Visitor{
	R visitBinaryExpr(Binary expr);
	R visitGroupingExpr(Grouping expr);
	R visitLiteralExpr(Literal expr);
	R visitUnaryExpr(Unary expr);

 };



static class Binary : Expr {
	public:
Binary( Expr left, Token operator, Expr right) : Expr(Expr) : operator(operator) : right(right){}

  Expr left;
 Token operator;
 Expr right;

 template<typename R>
 R accept(Visitor<R> visitor) {
	 return visitor.visitBinaryExpr(this);
}
}
static class Grouping : Expr {
	public:
Grouping( Expr expression) : Expr(Expr){}

  Expr expression;

 template<typename R>
 R accept(Visitor<R> visitor) {
	 return visitor.visitGroupingExpr(this);
}
}
static class Literal : Expr {
	public:
Literal( Object value) : Object(Object){}

  Object value;

 template<typename R>
 R accept(Visitor<R> visitor) {
	 return visitor.visitLiteralExpr(this);
}
}
static class Unary : Expr {
	public:
Unary( Token operator, Expr right) : Token(Token) : right(right){}

  Token operator;
 Expr right;

 template<typename R>
 R accept(Visitor<R> visitor) {
	 return visitor.visitUnaryExpr(this);
}
}
}
