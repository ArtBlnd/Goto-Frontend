#ifndef __GOTO_FRONTNED_LANGUAGE_C_LEXER_H__
#define __GOTO_FRONTNED_LANGUAGE_C_LEXER_H__

#include <string>
#include <vector>

#include <language/ILexer.h>

namespace Goto
{
namespace Basic
{
class Engine;
class FileViewer;
} // namespace Basic

namespace Language
{
namespace C
{

class Token;
class TokenUnknown;
class TokenLiteral;
class TokenSymbol;
class TokenIdentifier;
class TokenWhitespace;

enum class MacroType
{
    MACRO_UNKNOWN        = 0xFF,
    MACRO_DEFINE         = 0x01,
    MACRO_UNDEF          = 0x02,
    MACRO_IF             = 0x03,
    MACRO_ELSE           = 0x04,
    MACRO_ELSE_IF        = 0x05,
    MACRO_IF_DEF         = 0x06,
    MACRO_IF_NOT_DEF     = 0x07,
    MACRO_END_IF         = 0x08,
    MACRO_DEFINED        = 0x09,
    MACRO_INCLUDE_GLOBAL = 0x0A,
    MACRO_INCLUDE_LOCAL  = 0x0B,
};

class MacroFunc
{

};

class MacroFuncDefine : public MacroFunc
{
    std::vector<std::string> Operands;
    std::string              Expression;
};

class MacroFuncString : public MacroFunc
{
    std::string Expression;
};

class Macro
{
    std::string m_macroKey;

    MacroType m_mcrType   = MacroType::MACRO_UNKNOWN;
    size_t    m_mcrSize   = 0;
    size_t    m_mcrLine   = 0;
    size_t    m_mcrColumn = 0;

protected:
    Macro() = delete;
    Macro(MacroType type, size_t size, size_t line, size_t column);
    virtual ~Macro() = default;

public:
    bool IsMacroType(MacroType type) const;

    bool IsUnknown() const;
    bool IsMacroInclude() const;
    bool IsMacroIncludeGlobal() const;
    bool IsMacroIncludeLocal() const;
    bool IsMacroDefine() const;
    bool IsMacroUndef() const;
    bool IsMacroIf() const;
    bool IsMacroElse() const;
    bool IsMacroElseIf() const;
    bool IsMacroIfDefine() const;
    bool IsMacroIfNotDefine() const;
    bool IsMacroEndIf() const;
    bool IsMacroDefined() const;
    

    MacroType GetMacroType() const;

    void               SetKey(std::string key);
    const std::string& GetKey() const;

    void               SetExpr(std::string expr);
    const std::string& GetExpr() const;

    std::string ExpandIncludeExpr();
};

class MacroContext
{
    Macro* m_mcMacroBeg = nullptr;
    Macro* m_mcMacroEnd = nullptr;

public:
    Macro* GetPredefDate();
    Macro* GetPredefFile();
    Macro* GetPredefLine(Token* targetToken);
    Macro* GetPredefTime();

    void   InsertDefineTable(std::string Key, Macro* macro);
    void   RemoveDefineTable(std::string Key);
    Macro* LookupDefineTable(std::string key);
};

enum class TokenType
{
    TOKEN_UNKNOWN    = 0xFF,
    TOKEN_LITERAL    = 0x01,
    TOKEN_SYMBOL     = 0x02,
    TOKEN_IDENTIFIER = 0x03,
    TOKEN_WHITESPACE = 0x04
};

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
};

// Its a whitespace :)
class TokenWhitespace : Token
{
    friend class TokenContext;

protected:
    TokenWhitespace(size_t Size, size_t Line, size_t Column);

public:
};

// class TokenContext
// Information:
//      This contains token informations for parsed tokens with allocations.
class TokenContext
{
    Token* m_tcTokenBeg = nullptr;
    Token* m_tcTokenEnd = nullptr;

public:
    void InsertToken(Token* nextToken);

    Token* GetTokenBeg();
    Token* GetTokenEnd();

    bool isEmpty() const;
};

class Lexer : public ILexer
{
    TokenContext* lxTokenContext = nullptr;
    MacroContext* lxMacroContext = nullptr;

    Token* AllocateToken(TokenType type);
    Token* AllocateToken(TokenType type, std::string str);
    Token* AllocateToken(TokenType type, char c);

    Macro* AllocateMacro(MacroType type);
    Macro* AllocateMacro(MacroType type, std::string expr);

    std::string lxGetNextFilenameFromInclude(bool& isLocalPath);
    std::string lxGetNextIdentifierOnScope();
    std::string lxGetNextStringLiteralOnScope();

    Macro* lxTokenlizeNextMacro();

public:
    Lexer() = delete;
    Lexer(TokenContext* tContext, MacroContext* mContext, const char* srcFileBuf, size_t srcFileLen);

    bool lxStartTokenlizeSourceCode();
};

// Tokenlize source code to TokenContext
bool lxTokenlizeSourceCode(TokenContext* tokenContext,
                           MacroContext* macroContext,
                           const char*   srcFileBuf,
                           size_t        srcFileLen);

} // namespace C
} // namespace Language
} // namespace Goto

#endif