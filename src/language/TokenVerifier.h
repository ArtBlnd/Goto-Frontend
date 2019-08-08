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
        // Type : '+' (PLUS)
        constexpr char TK_PLUS_SYM = '+';
        inline bool tvIsPlusSym(const char c)
        {
            return c == '+';
        }

        // Token Verifier
        // Type : '-' (MINUS)
        constexpr char TK_MINUS_SYM = '-';
        inline bool tvIsMinusSym(const char c)
        {
            return c == '-';
        }

        // Token Verifier
        // Type : ':' (COLON)
        constexpr char TK_COLON = ':';
        inline bool tvIsColon(const char c)
        {
            return c == ':';
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
        // Type : '\n' (NEXT_LINE)
        constexpr char TK_NEXT_LINE = '\n';
        inline bool tvIsNextLine(const char c)
        {
            return c == '\n';
        }

        // Token Verifier
        // Type : '\\' (BACK_SLASH)
        constexpr char TK_BACK_SLASH = '\\';
        inline bool tvIsBackSlash(const char c)
        {
            return c == '\\';
        }

        // Token Verifier
        // Type : '@' (AT)
        constexpr char TK_AT_SYM = '@';
        inline bool tvIsAtSym(const char c)
        {
            return c == '@';
        }

        // Token Verifier
        // Type : '^' (XOR)
        constexpr char TK_XOR_SYM = '^';
        inline bool tvIsXorSym(const char c)
        {
            return c == '^';
        }

        // Token Verifier
        // Type : '%' (MOD)
        constexpr char TK_MOD_SYM = '%';
        inline bool tvIsModSym(const char c)
        {
            return c == '%';
        }

        // Token Verifier
        // Type : '&' (AND)
        constexpr char TK_AND_SYM = '&';
        inline bool tvIsAndSym(const char c)
        {
            return c == '&';
        }

        // Token Verifier
        // Type : '!' (NOT)
        constexpr char TK_NOT_SYM = '!';
        inline bool tvIsNotSym(const char c)
        {
            return c == '!';
        }

        // Token Verifier
        // Type : '=' (EQUAL)
        constexpr char TK_EQUAL_SYM = '=';
        inline bool tvIsEqualSym(const char c)
        {
            return c == '=';
        }

        // Token Verifier
        // Type : '>' (GREATER_THAN)
        constexpr char TK_GREATER_THAN_SYM = '>';
        inline bool tvIsGreaterThanSym(const char c)
        {
            return c == '>';
        }

        // Token Verifier
        // Type : '<' (LESS_THAN)
        constexpr char TK_GREATER_THAN_SYM = '<';
        inline bool tvIsLessThanSym(const char c)
        {
            return c == '<';
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
        // Type : '{, }' (BRACKET)
        constexpr char TK_BRACKET_OPENED = '{';
        constexpr char TK_BRACKET_CLOSED = '}';
        inline bool tvIsBracket(const char c, bool isClosed)
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
        bool tvIsAlphabet(const char c);

        inline bool tvIsSpecalSym(const char c)
        {
            return tvIsColon(c)          | // :
                   tvIsSemicolon(c)      | // ;
                   tvIsEqualSym(c)       | // =
                   tvIsComma(c)          | // ,
                   tvIsDot(c)            | // .
                   tvIsAsterisk(c)       | // *
                   tvIsSharp(c)          | // #
                   tvIsPlusSym(c)        | // +
                   tvIsMinusSym(c)       | // -
                   tvIsNotSym(c)         | // !
                   tvIsXorSym(c)         | // ^
                   tvIsModSym(c)         | // %
                   tvIsAndSym(c)         | // &
                   tvIsAtSym(c)          | // @
                   tvIsBracket(c, true)  | // {
                   tvIsBracket(c, false) | // }
                   tvIsParen(c, true)    | // (
                   tvIsParen(c, false)   | // )
                   tvIsGreaterThanSym(c) | // >
                   tvIsLessThanSym(c);     // <
        }

        // Fast token comparer if its under 16 bytes.
        // this use normalization which is change 16 byte char array into integer and compare.
        bool tvFastStrCmp16(const std::string& str1, const std::string& str2);
    }
}


#endif