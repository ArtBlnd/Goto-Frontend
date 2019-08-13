#include <Language/Token.h>
#include <Language/TokenTable.h>

namespace Goto
{
namespace Language
{

// ============================================
// Token Implements
// ============================================

Token::Token(TokenType Type, size_t Size, size_t Line, size_t Column)
{
    m_tkType   = Type;
    m_tkSize   = Size;
    m_tkLine   = Line;
    m_tkColumn = Column;
}

bool Token::IsTokenEnd() const
{
    return m_tkNext == nullptr;
}

bool Token::IsTokenBegin() const
{
    return m_tkPrev == nullptr;
}

size_t Token::GetSize() const
{
    return m_tkSize;
}

size_t Token::GetLine() const
{
    return m_tkLine;
}

size_t Token::GetColumn() const
{
    return m_tkColumn;
}

TokenType Token::GetTypeOf() const
{
    return m_tkType;
}

bool Token::IsTypeOf(TokenType type) const
{
    return GetTypeOf() == type;
}

bool Token::IsUnknownType() const
{
    return IsTypeOf(TokenType::TOKEN_UNKNOWN);
}

TokenUnknown* Token::AsUnknown()
{
    if (IsUnknownType())
    {
        return (TokenUnknown*)this;
    }

    return nullptr;
}

bool Token::IsLiteralType() const
{
    return IsTypeOf(TokenType::TOKEN_LITERAL);
}

TokenLiteral* Token::AsLiteral()
{
    if (IsLiteralType())
    {
        return (TokenLiteral*)this;
    }

    return nullptr;
}

bool Token::IsSymbolType() const
{
    return IsTypeOf(TokenType::TOKEN_SYMBOL);
}

TokenSymbol* Token::AsSymbol()
{
    if (IsSymbolType())
    {
        return (TokenSymbol*)this;
    }

    return nullptr;
}

bool Token::IsIdentifierType() const
{
    return IsTypeOf(TokenType::TOKEN_IDENTIFIER);
}

TokenIdentifier* Token::AsIdentifier()
{
    if (IsIdentifierType())
    {
        return (TokenIdentifier*)this;
    }

    return nullptr;
}

bool Token::IsWhitesapceType() const
{
    return IsTypeOf(TokenType::TOKEN_WHITESPACE);
}

TokenWhitespace* Token::AsWhitespace()
{
    if (IsWhitesapceType())
    {
        return (TokenWhitespace*)this;
    }

    return nullptr;
}

// ============================================
// Token Unknown Implements
// ============================================

TokenUnknown::TokenUnknown(size_t Line, size_t Column, char UnknownToken)
    : Token(TokenType::TOKEN_UNKNOWN, 1 /* One Char */, Line, Column)
{
    m_tkUnknown = UnknownToken;
}

bool TokenUnknown::IsToken(char token) const
{
    return m_tkUnknown == token;
}

constexpr char TokenUnknown::Get() const
{
    return m_tkUnknown;
}

// ============================================
// Token Literal Implements
// ============================================

TokenLiteral::TokenLiteral(size_t Line, size_t Column, std::string SymbolLiteral)
    : Token(TokenType::TOKEN_LITERAL, SymbolLiteral.length(), Line, Column)
{
    m_tkLiteral = std::move(SymbolLiteral);
}

bool TokenLiteral::IsToken(std::string token) const
{
    return token == m_tkLiteral;
}

bool TokenLiteral::IsToken(const std::string& token) const
{
    return token == m_tkLiteral;
}

bool TokenLiteral::IsStringLiteral() const
{
    return !IsFloatingLiteral() && !IsIntegerLiteral();
}

bool TokenLiteral::IsFloatingLiteral() const
{
    // TODO : implements
    return true;
}

bool TokenLiteral::IsIntegerLiteral() const
{
    // TODO : implements
    return true;
}

std::string TokenLiteral::Get() const
{
    return m_tkLiteral;
}

// ============================================
// Token Symbol Implements
// ============================================

TokenSymbol::TokenSymbol(size_t Line, size_t Column, char SymbolToken)
    : Token(TokenType::TOKEN_SYMBOL, 1 /* One Char */, Line, Column)
{
    m_tkSymbol = SymbolToken;
}

char TokenSymbol::Get() const
{
    return m_tkSymbol;
}

bool TokenSymbol::IsToken(char token) const
{
    return m_tkSymbol == token;
}

bool TokenSymbol::IsSymbolParen(bool isClosed) const
{
    return ttIsParen(Get(), isClosed);
}

bool TokenSymbol::IsSymbolSquare(bool isClosed) const
{
    return ttIsSquare(Get(), isClosed);
}

bool TokenSymbol::IsSymbolCurly(bool isClosed) const
{
    return ttIsBracket(Get(), isClosed);
}

bool TokenSymbol::IsSymbolSemicolon() const
{
    return ttIsSemicolon(Get());
}

bool TokenSymbol::IsSymbolAsterisk() const
{
    return ttIsAsterisk(Get());
}

// ============================================
// Token Identifier Implements
// ============================================

TokenIdentifier::TokenIdentifier(size_t Line, size_t Column, std::string IdentifierToken)
    : Token(TokenType::TOKEN_IDENTIFIER, IdentifierToken.size(), Line, Column)
{
    m_tkIdentifier = IdentifierToken;
}

// ============================================
// Token Whitespace Implements
// ============================================

TokenWhitespace::TokenWhitespace(size_t Size, size_t Line, size_t Column)
    : Token(TokenType::TOKEN_WHITESPACE, Size, Line, Column)
{
}

} // namespace Language
} // namespace Goto