add_library(goto-language-c STATIC
    ${GOTO_LANGUAGE_SRC}
    Parser.cpp
    Parser.h
    TokenVerifier.cpp
    TokenVerifier.h
)