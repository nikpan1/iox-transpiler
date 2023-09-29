## About The Project
### *MediT* - Yet another mediocre transpiler
My approach to writing a simple transpiler while reading books, so I can easier memorize it.
For now It's mostly made as the author of craftinginterpreters proposes, but in the future there will be a bigger approach with more features.

## About The Language
 Simple naming conventions (python like) with expression rules exactly like in C (Give me my increments! ++).

## Implemented
- Scanner (Token Type with error handling)
- Syntax tree (implemented with the visitor pattern)
- Printer (for syntax tree unitesting)
- Parser (recursive descent parsing)
- Reporting (Syntax errors on runtime)

## TODO
- Implementing function structures mechanics and OOP
- Inheritance and polimorphysm.


# Keywords map

Keywords can be found in the src/Core.cpp file.

## Expression grammar

expression     → equality ;
equality       → comparison ( ( "!=" | "==" ) comparison )* ;
comparison     → term ( ( ">" | ">=" | "<" | "<=" ) term )* ;
term           → factor ( ( "-" | "+" ) factor )* ;
factor         → unary ( ( "/" | "*" ) unary )* ;
unary          → ( "!" | "-" ) unary
               | primary ;
primary        → NUMBER | STRING | "true" | "false" | "nil"
               | "(" expression ")" ;

## Sources 
- craftinginterpreters.com
- Compilers: Principles, Techniques, and Tools
- youtube.com


<img src="https://media1.giphy.com/media/NLHq5dOtUtOUEjOr7W/giphy.gif?cid=ecf05e475spjqp1xa8l3lbcwziheudrk2pc56hpxyzz5us9k&ep=v1_gifs_search&rid=giphy.gif&ct=g">
