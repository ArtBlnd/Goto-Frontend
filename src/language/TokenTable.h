#ifndef __GTFW_C_FRONTEND_LANGUAGE_TOKEN_VERIFIER_H__
#define __GTFW_C_FRONTEND_LANGUAGE_TOKEN_VERIFIER_H__

#include <string>
#include <functional>

namespace Goto
{
namespace Language
{
// Type: '\"' (DOUBLE_QUOTE)
constexpr char TK_DOUBLE_QUOTE = '\"';
inline bool    ttIsDoubleQuote(const char c)
{
    return c == '\"';
}

// Type: '\'' (SINGLE_QUOTE)
constexpr char TK_SINGLE_QUOTE = '\'';
inline bool    ttIsSingleQuote(const char c)
{
    return c == '\'';
}

// Type : '+' (PLUS)
constexpr char TK_PLUS_SYM = '+';
inline bool    ttIsPlusSym(const char c)
{
    return c == '+';
}

// Type : '-' (MINUS)
constexpr char TK_MINUS_SYM = '-';
inline bool    ttIsMinusSym(const char c)
{
    return c == '-';
}

// Type : ':' (COLON)
constexpr char TK_COLON = ':';
inline bool    ttIsColon(const char c)
{
    return c == ':';
}

// Type : ';' (SEMI_COLON)
constexpr char TK_SEMI_COLON = ';';
inline bool    ttIsSemicolon(const char c)
{
    return c == ';';
}

// Type : ',' (COMMA)
constexpr char TK_COMMA = ',';
inline bool    ttIsComma(const char c)
{
    return c == ',';
}

// Type : '.' (DOT)
constexpr char TK_DOT = '.';
inline bool    ttIsDot(const char c)
{
    return c == '.';
}

// Type : ' ' (SPACE)
constexpr char TK_SPACE = ' ';
inline bool    ttIsSpace(const char c)
{
    return c == ' ';
}

// Type : '\n' (NEXT_LINE)
constexpr char TK_NEXT_LINE = '\n';
inline bool    ttIsNextLine(const char c)
{
    return c == '\n';
}

// Type : '\\' (BACK_SLASH)
constexpr char TK_BACK_SLASH = '\\';
inline bool    ttIsBackSlash(const char c)
{
    return c == '\\';
}

// Type : '@' (AT)
constexpr char TK_AT_SYM = '@';
inline bool    ttIsAtSym(const char c)
{
    return c == '@';
}

// Type : '^' (XOR)
constexpr char TK_XOR_SYM = '^';
inline bool    ttIsXorSym(const char c)
{
    return c == '^';
}

// Type : '%' (MOD)
constexpr char TK_MOD_SYM = '%';
inline bool    ttIsModSym(const char c)
{
    return c == '%';
}

// Type : '&' (AND)
constexpr char TK_AND_SYM = '&';
inline bool    ttIsAndSym(const char c)
{
    return c == '&';
}

// Type : '!' (NOT)
constexpr char TK_NOT_SYM = '!';
inline bool    ttIsNotSym(const char c)
{
    return c == '!';
}

// Type : '=' (EQUAL)
constexpr char TK_EQUAL_SYM = '=';
inline bool    ttIsEqualSym(const char c)
{
    return c == '=';
}

// Type : '>' (GREATER_THAN)
constexpr char TK_GREATER_THAN_SYM = '>';
inline bool    ttIsGreaterThanSym(const char c)
{
    return c == '>';
}

// Type : '<' (LESS_THAN)
constexpr char TK_GREATER_THAN_SYM = '<';
inline bool    ttIsLessThanSym(const char c)
{
    return c == '<';
}

// Type : '(, )' (PAREN)
constexpr char TK_PAREN_OPENED = '(';
constexpr char TK_PAREN_CLOSED = ')';
inline bool    ttIsParen(const char c, bool isClosed)
{
    return isClosed ? c == ')' : c == '(';
}

// Type : '[, ]' (SQUARE)
constexpr char TK_SQUARE_OPENED = '[';
constexpr char TK_SQUARE_CLOSED = ']';
inline bool    ttIsSquare(const char c, bool isClosed)
{
    return isClosed ? c == ']' : c == '[';
}

// Type : '{, }' (BRACKET)
constexpr char TK_BRACKET_OPENED = '{';
constexpr char TK_BRACKET_CLOSED = '}';
inline bool    ttIsBracket(const char c, bool isClosed)
{
    return isClosed ? c == '}' : c == '{';
}

// Type : '*' (ASTERISK)
constexpr char TK_ASTERISK = '*';
inline bool    ttIsAsterisk(const char c)
{
    return c == '*';
}

// Type : '#' (SHARP)
constexpr char TK_SHARP = '#';
inline bool    ttIsSharp(const char c)
{
    return c == '#';
}

// Type : '1|2|3|4|5|6|7|8|9|0' (INTERGERS)
bool ttIsInteger(const std::string& str);

// Type : 'true|false|0|1' (BOOLEANDS)
bool ttIsBoolean(const std::string& str);

// Type : 'a > | z <' (ALPHABET)
bool ttIsAlphabet(const char c);

class ttIsMacroOperandEndFunc
{
    bool isBackslashFound = false;

public:
    bool operator()(char c)
    {
        if (ttIsBackSlash(c))
        {
            isBackslashFound = true;
        }
        if (ttIsNextLine(c))
        {
            if (isBackslashFound)
            {
                isBackslashFound = false;
            }
            else
            {
                return true;
            }
        }
        return false;
    }
};

#define ttIsMacroOperandEnd ttIsMacroOperandEndFunc()

inline std::function<bool(char)> ttInverse(std::function<bool(char)> func)
{
    return [=](char c) { return !func(c); };
}

inline std::function<bool(char)> ttInverse(char token)
{
    return [=](char c) { return c != token; };
}

// Fast token comparer if its under 16 bytes.
// this use normalization which is change 16 byte char array into integer and compare.
bool ttFastStrCmp16(const std::string& str1, const std::string& str2);

} // namespace Language
} // namespace Goto

#endif