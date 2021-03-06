#ifndef __GOTO_FRONEND_LANGUAGE_TOKEN_H__
#define __GOTO_FRONEND_LANGUAGE_TOKEN_H__

#include <string>

namespace Goto
{
namespace Language
{

enum class TokenType
{
    TOKEN_UNKNOWN    = 0xFF,
    TOKEN_LITERAL    = 0x01,
    TOKEN_SYMBOL     = 0x02,
    TOKEN_IDENTIFIER = 0x03,
    TOKEN_WHITESPACE = 0x04
};

class Token;
class TokenUnknown;
class TokenLiteral;
class TokenSymbol;
class TokenIdentifier;
class TokenWhitespace;

// class Token
// Description :
//      Base class of all token objects
//      contains basic information of token object, such as size, line, colum, type.
class Token
{
    TokenType m_tkType   = TokenType::TOKEN_UNKNOWN;
    size_t    m_tkSize   = 0;
    size_t    m_tkLine   = 0;
    size_t    m_tkColumn = 0;

protected:
    Token() = delete;
    Token(TokenType Type, size_t Size, size_t Line, size_t Column);

public:
    Token* m_tkNext = nullptr;
    Token* m_tkPrev = nullptr;

    bool IsTokenEnd() const;
    bool IsTokenBegin() const;

    size_t GetSize() const;
    size_t GetLine() const;
    size_t GetColumn() const;

    TokenType GetTypeOf() const;
    bool      IsTypeOf(TokenType type) const;

    bool          IsUnknownType() const;
    TokenUnknown* AsUnknown();

    bool          IsLiteralType() const;
    TokenLiteral* AsLiteral();

    bool         IsSymbolType() const;
    TokenSymbol* AsSymbol();

    bool             IsIdentifierType() const;
    TokenIdentifier* AsIdentifier();

    bool             IsWhitesapceType() const;
    TokenWhitespace* AsWhitespace();
};

class TokenUnknown : Token
{
    friend class TokenContext;
    char m_tkUnknown;

protected:
    TokenUnknown(size_t Line, size_t Column, char UnknownToken);

public:
    bool           IsToken(char token) const;
    constexpr char Get() const;
};

class TokenLiteral : Token
{
    friend class TokenContext;
    std::string m_tkLiteral;

protected:
    TokenLiteral(size_t Line, size_t Column, std::string LiteralToken);

public:
    bool IsToken(std::string token) const;
    bool IsToken(const std::string& token) const;

    bool IsStringLiteral() const;
    bool IsFloatingLiteral() const;
    bool IsIntegerLiteral() const;

    std::string Get() const;
};

// This can contain symbol such as <, {, }, #, @ that something isn't a charactor.
class TokenSymbol : Token
{
    friend class TokenContext;
    char m_tkSymbol;

protected:
    TokenSymbol(size_t Line, size_t Column, char SymbolToken);

public:
    bool IsToken(char token) const;

    bool IsSymbolParen(bool isClosed) const;
    bool IsSymbolSquare(bool isClosed) const;
    bool IsSymbolCurly(bool isClosed) const;
    bool IsSymbolSemicolon() const;
    bool IsSymbolAsterisk() const;

    char Get() const;
};

class TokenIdentifier : Token
{
    friend class TokenContext;
    std::string m_tkIdentifier;

protected:
    TokenIdentifier(size_t Line, size_t Column, std::string IdentifierToken);

public:
    const std::string& GetIdentifier();
};

// Its a whitespace :)
class TokenWhitespace : Token
{
    friend class TokenContext;

protected:
    TokenWhitespace(size_t Size, size_t Line, size_t Column);

public:
};

} // namespace Language
} // namespace Goto

#endif