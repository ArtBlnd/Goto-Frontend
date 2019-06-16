#ifndef __GFWK_C_FRONTEND_PARSER_TOKEN_VERIFIER_H__
#define __GFWK_C_FRONTEND_PARSER_TOKEN_VERIFIER_H__

#include <string>

namespace GTFW
{
    namespace Parser
    {
        // Token Verifier
        // Type: '\"' (DOUBLE_QUOTE)
        inline bool tvIsDoubleQuote(const char c)
        {
            return c == '\"';
        }

        // Token Verifier
        // Type: '\'' (SINGLE_QUOTE)
        inline bool tvIsSingleQuote(const char c)
        {
            return c == '\'';
        }

        // Token Verifier
        // Type : '-' (DASH)
        inline bool tvIsDash(const char c)
        {
            return c == '-';
        }

        // Token Verifier
        // Type : ';' (SEMI_COLON)
        inline bool tvIsSemicolon(const char c)
        {
            return c == ';';
        }

        // Token Verifier
        // Type : ',' (COMMA)
        inline bool tvIsComma(const char c)
        {
            return c == ',';
        }

        // Token Verifier
        // Type : '.' (DOT)
        inline bool tvIsDot(const char c)
        {
            return c == '.';
        }

        // Token Verifier
        // Type : ' ' (SPACE)
        inline bool tvIsSpace(const char c)
        {
            return c == ' ';
        }

        // Token Verifier
        // Type : '=' (EQUAL)
        inline bool tvIsEqualSym(const char c)
        {
            return c == '=';
        }
        
        // Token Verifier
        // Type : '(, )' (PAREN)
        inline bool tvIsParen(const char c, bool isClosed)
        {
            return isClosed ? c == ')' : c == '(';
        }

        // Token Verifier
        // Type : '[, ]' (SQUARE)
        inline bool tvIsSquare(const char c, bool isClosed)
        {
            return isClosed ? c == ']' : c == '[';
        }

        // Token Verifier
        // Type : '{, }' (CURLY)
        inline bool tvIsCurly(const char c, bool isClosed)
        {
            return isClosed ? c == '}' : c == '{';
        }

        // Token Verifier
        // Type : '*' (ASTERISK)
        inline bool tvIsAsterisk(const char c)
        {
            return c == '*';
        }

        // Token Verifier
        // Type : '1|2|3|4|5|6|7|8|9|0' (INTERGERS)
        bool tvIsInteger(const std::string& str);

        // Token Verifier
        // Type : 'true|false|0|1' (BOOLEANDS)
        bool tvIsBoolean(const std::string& str);

        // Token Verifier
        // Type : 'a > | z <' (ALPHABET)
        bool tvIsAlphabet(const std::string& str);
    }
}


#endif