add_library(lox)

target_include_directories(lox 
  PUBLIC
    ${lox_SOURCE_DIR}/Expr
  )

target_source(lox 
  PRIVATE
    Lox.cpp
    AstPrinter.cpp
    Scanner.cpp
    Token.cpp

    main.cpp
    errorLog.cpp
  )



