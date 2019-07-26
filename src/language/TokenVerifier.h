#ifndef __GTFW_C_FRONTEND_LANGUAGE_TOKEN_VERIFIER_H__
#define __GTFW_C_FRONTEND_LANGUAGE_TOKEN_VERIFIER_H__

#include <string>

namespace Goto
{
    namespace Language
    {
        // Token Verifier
        // Type: '\"' (DOUBLE_QUOTE)
        constexpr char TK_DOUBLE_QUOTE = '\"';
        inline bool tvIsDoubleQuote(const char c)
        {
            return c == '\"';
        }

        // Token Verifier
        // Type: '\'' (SINGLE_QUOTE)
        constexpr char TK_SINGLE_QUOTE = '\'';
        inline bool tvIsSingleQuote(const char c)
        {
            return c == '\'';
        }

        // Token Verifier
        // Type : '-' (DASH)
        constexpr char TK_DASH = '-';
        inline bool tvIsDash(const char c)
        {
            return c == '-';
        }

        // Token Verifier
        // Type : ';' (SEMI_COLON)
        constexpr char TK_SEMI_COLON = ';';
        inline bool tvIsSemicolon(const char c)
        {
            return c == ';';
        }

        // Token Verifier
        // Type : ',' (COMMA)
        constexpr char TK_COMMA = ',';
        inline bool tvIsComma(const char c)
        {
            return c == ',';
        }

        // Token Verifier
        // Type : '.' (DOT)
        constexpr char TK_DOT = '.';
        inline bool tvIsDot(const char c)
        {
            return c == '.';
        }

        // Token Verifier
        // Type : ' ' (SPACE)
        constexpr char TK_SPACE = ' ';
        inline bool tvIsSpace(const char c)
        {
            return c == ' ';
        }

        // Token Verifier
        // Type : '=' (EQUAL)
        constexpr char TK_EQUAL_SYM = '=';
        inline bool tvIsEqualSym(const char c)
        {
            return c == '=';
        }
        
        // Token Verifier
        // Type : '(, )' (PAREN)
        constexpr char TK_PAREN_OPENED = '(';
        constexpr char TK_PAREN_CLOSED = ')';
        inline bool tvIsParen(const char c, bool isClosed)
        {
            return isClosed ? c == ')' : c == '(';
        }

        // Token Verifier
        // Type : '[, ]' (SQUARE)
        constexpr char TK_SQUARE_OPENED = '[';
        constexpr char TK_SQUARE_CLOSED = ']';
        inline bool tvIsSquare(const char c, bool isClosed)
        {
            return isClosed ? c == ']' : c == '[';
        }

        // Token Verifier
        // Type : '{, }' (CURLY)
        constexpr char TK_CURLY_OPENED = '{';
        constexpr char TK_CURLY_CLOSED = '}';
        inline bool tvIsCurly(const char c, bool isClosed)
        {
            return isClosed ? c == '}' : c == '{';
        }

        // Token Verifier
        // Type : '*' (ASTERISK)
        constexpr char TK_ASTERISK = '*';
        inline bool tvIsAsterisk(const char c)
        {
            return c == '*';
        }

        // Token Verifier
        // Type : '#' (SHARP)
        constexpr char TK_SHARP = '#';
        inline bool tvIsSharp(const char c)
        {
            return c == '#';
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