#include "basic/Debug.h"

#include "language/TokenTable.h"
#include "language/C/Lexer.h"

namespace Goto
{
namespace Language
{
namespace C
{

inline bool IsSpecalSym(const char c)
{
    return ttIsColon(c) |          // :
           ttIsSemicolon(c) |      // ;
           ttIsEqualSym(c) |       // =
           ttIsComma(c) |          // ,
           ttIsDot(c) |            // .
           ttIsAsterisk(c) |       // *
           ttIsSharp(c) |          // #
           ttIsPlusSym(c) |        // +
           ttIsMinusSym(c) |       // -
           ttIsNotSym(c) |         // !
           ttIsXorSym(c) |         // ^
           ttIsModSym(c) |         // %
           ttIsAndSym(c) |         // &
           ttIsAtSym(c) |          // @
           ttIsBracket(c, true) |  // {
           ttIsBracket(c, false) | // }
           ttIsParen(c, true) |    // (
           ttIsParen(c, false) |   // )
           ttIsGreaterThanSym(c) | // >
           ttIsLessThanSym(c);     // <
}

inline bool IsSeperator(const char c)
{
    return ttIsColon(c) |          // :
           ttIsSpace(c) |          //
           ttIsNextLine(c) |       // \n
           ttIsSemicolon(c) |      // ;
           ttIsEqualSym(c) |       // =
           ttIsComma(c) |          // ,
           ttIsDot(c) |            // .
           ttIsAsterisk(c) |       // *
           ttIsSharp(c) |          // #
           ttIsPlusSym(c) |        // +
           ttIsMinusSym(c) |       // -
           ttIsNotSym(c) |         // !
           ttIsXorSym(c) |         // ^
           ttIsModSym(c) |         // %
           ttIsAndSym(c) |         // &
           ttIsAtSym(c) |          // @
           ttIsBracket(c, true) |  // {
           ttIsBracket(c, false) | // }
           ttIsParen(c, true) |    // (
           ttIsParen(c, false) |   // )
           ttIsGreaterThanSym(c) | // >
           ttIsLessThanSym(c);     // <
}

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

// ============================================
// TokenContext Implements
// ============================================
void TokenContext::InsertToken(Token* nextToken) {}

// ============================================
// Macro Implements section
// ============================================

Macro::Macro(MacroType type, size_t size, size_t line, size_t column)
    : m_mcrType(type), m_mcrSize(size), m_mcrLine(line), m_mcrColumn(column)
{
}

bool Macro::IsMacroType(MacroType type) const
{
    return m_mcrType == type;
}

bool Macro::IsUnknown() const
{
    return IsMacroType(MacroType::MACRO_UNKNOWN);
}

bool Macro::IsMacroInclude() const
{
    return IsMacroIncludeLocal() | IsMacroIncludeGlobal();
}

bool Macro::IsMacroDefine() const
{
    return IsMacroType(MacroType::MACRO_DEFINE);
}

bool Macro::IsMacroUndef() const
{
    return IsMacroType(MacroType::MACRO_UNDEF);
}

bool Macro::IsMacroIf() const
{
    return IsMacroType(MacroType::MACRO_IF);
}

bool Macro::IsMacroElse() const
{
    return IsMacroType(MacroType::MACRO_ELSE);
}

bool Macro::IsMacroElseIf() const
{
    return IsMacroType(MacroType::MACRO_ELSE_IF);
}

bool Macro::IsMacroIfDefine() const
{
    return IsMacroType(MacroType::MACRO_IF_DEF);
}

bool Macro::IsMacroIfNotDefine() const
{
    return IsMacroType(MacroType::MACRO_IF_NOT_DEF);
}

bool Macro::IsMacroEndIf() const
{
    return IsMacroType(MacroType::MACRO_END_IF);
}

bool Macro::IsMacroDefined() const
{
    return IsMacroType(MacroType::MACRO_DEFINED);
}

bool Macro::IsMacroIncludeGlobal() const
{
    return IsMacroType(MacroType::MACRO_INCLUDE_GLOBAL);
}

bool Macro::IsMacroIncludeLocal() const
{
    return IsMacroType(MacroType::MACRO_INCLUDE_LOCAL);
}

bool Macro::IsMacroPragma() const
{
    return IsMacroType(MacroType::MACRO_PRAGMA);
}

bool Macro::IsMacroError() const
{
    return IsMacroType(MacroType::MACRO_ERROR);
}

MacroType Macro::GetMacroType() const
{
    return m_mcrType;
}

void Macro::SetKey(std::string key)
{
    m_macroKey = std::move(key);
}

const std::string& Macro::GetKey() const
{
    return m_macroKey;
}

// ============================================
// Lexer implements section.
// ============================================

Token* Lexer::AllocateToken(TokenType type) {}
Token* Lexer::AllocateToken(TokenType type, std::string str) {}
Token* Lexer::AllocateToken(TokenType type, char c) {}

Macro* Lexer::AllocateMacro(MacroType type) {}
Macro* Lexer::AllocateMacro(MacroType type, std::string expr) {}

/* lxTokenlizeSourceCode
 *
 * Description:
 *      Parse macro tokens and records in mContext table.
 *      so that we can use macros when we are tokenlizing target source file.
 * Params :
 *      - tContext : context that contains current parsed tokens in this instance
 *      - mContext : context that contains current parsed macros in this instance
 *      - srcFileBuf : target source file buffer
 *      - srcFileLen : target source file length
 * Returns :
 *      Returning true if successed to tokenlzie source code
 */
bool lxTokenlizeSourceCode(TokenContext* tContext, MacroContext* mContext, const char* srcFileBuf, size_t srcFileLen)
{
    Lexer lexer = Lexer(tContext, mContext, srcFileBuf, srcFileLen);
    return lexer.lxStartTokenlizeSourceCode();
}

//
// Lexer Implements
//
Lexer::Lexer(TokenContext* tContext, MacroContext* mContext, const char* srcFileBuf, size_t srcFileLen)
    : lxTokenContext(tContext), lxMacroContext(mContext), ILexer(srcFileBuf, srcFileLen)
{
    noway_assert(lxTokenContext, "Token context cannot be nullptr!");
    noway_assert(lxMacroContext, "Macro context cannot be nullptr!");
    noway_assert(lxSrcFileBuf, "Source file buffer cannot be nullptr!");
    noway_assert(lxSrcFileLen, "Source file length cannot be zero!");
}

bool Lexer::lxStartTokenlizeSourceCode()
{
    while (lxIsEOF())
    {
        const char c = lxGetCurrChar();

        // We are trying to handle macros first
        // parse it from lxTokenlizeNextMacro and identify it.
        // some macros will be applied at this point.
        if (ttIsSharp(c))
        {
            Macro* newMacro = lxTokenlizeNextMacro();

            // Handling includes
            if (newMacro->IsMacroInclude())
            {
                const std::string& includePath = newMacro->GetKey();

                if (!lxTryIncludeFile(includePath, newMacro->IsMacroIncludeLocal()))
                {
                    // TODO emit error.
                }
            }

            if (newMacro->IsMacroDefine())
            {
                if (lxMacroContext->LookupDefineTable(newMacro->GetKey()) != nullptr)
                {
                    // Same macro is on macro table. emit warning.
                }
                else
                {
                    lxMacroContext->InsertDefineTable(newMacro->GetKey(), newMacro);
                }
            }
            if (newMacro->IsMacroUndef())
            {
                lxMacroContext->RemoveDefineTable(newMacro->GetKey());
            }
        }
    }

    return false;
}

/* lxGetNextIdentifierOnScope
 *
 * Description :
 *      Parse string that is not a specal symbols
 * Returns :
 *      return parsed identifier string
 */
std::string Lexer::lxGetNextIdentifierOnScope()
{
    noway_assert(IsSpecalSym(lxGetCurrChar()), "Identifier should not start with specal symbols!");

    std::string identifier;
    while (lxIsEOF())
    {
        char c = lxGetCurrChar();

        if (IsSpecalSym(c))
        {
            break;
        }

        identifier += c;
        lxConsumeChar();
    }

    return identifier;
}

/* lxGetNextStringLiteralOnScope
 *
 * Description:
 *     Parse string that contains in literal, which is ' or "
 * Returns :
 *     return parsed string of literal
 */
std::string Lexer::lxGetNextStringLiteralOnScope()
{
    noway_assert(ttIsDoubleQuote(lxGetPrivChar()), "Cannot extract string from string literal!");
    std::string literal;

    while (lxIsEOF())
    {
        char c = lxConsumeAndGetChar();

        literal += c;
        if (ttIsDoubleQuote(c))
        {
            break;
        }
    }

    return literal;
}

/* lxGetNextFilenameFromInclude
 *
 * Description:
 *     Parse filename from next char of include macro token.
 * Params :
 *      - isLocalPath : Is this path is for local?
 * Returns :
 *     return parsed string of literal
 */
std::string Lexer::lxGetNextFilenameFromInclude(bool& isLocalPath)
{
    const char initialC = lxConsumeAndGetChar();
    noway_assert(ttIsSpace(initialC) || ttIsDoubleQuote(initialC) || ttIsLessThanSym(initialC),
                 "Cannot extract include path from string!");

    std::string fileName;

    bool startRecord = false;
    while (lxIsEOF())
    {
        char c = lxConsumeAndGetChar();

        if (startRecord)
        {
            fileName += c;
            if (ttIsGreaterThanSym(c))
            {
                break;
            }
        }

        // We are skipping space that in between < or " and end of `e` which is end of include token
        if (ttIsSpace(c))
        {
            continue;
        }

        // Start parsig "`string`"
        if (ttIsDoubleQuote(c))
        {
            fileName    = lxGetNextStringLiteralOnScope();
            isLocalPath = true;
            break;
        }

        // Start parsing <`string`>
        if (ttIsLessThanSym(c))
        {
            isLocalPath = false;
            startRecord = true;
        }

        // TODO : replace assert to source trace.
        noway_assert(true, "[INTERNAL] failed to find start of define token");
    }

    return fileName;
}

// Macro keyword token table.
namespace MacroKeyword
{

const std::string MK_DEFINE     = "define";
const std::string MK_UNDEF      = "undef";
const std::string MK_IF         = "if";
const std::string MK_ELSE       = "else";
const std::string MK_ELSE_IF    = "elif";
const std::string MK_IF_DEF     = "ifdef";
const std::string MK_IF_NOT_DEF = "ifndef";
const std::string MK_END_IF     = "endif";
const std::string MK_DEFINED    = "defined";
const std::string MK_INCLUDE    = "include";

} // namespace MacroKeyword

/* lxTokenlizeMacro
 *
 * Description:
 *      Parse macro tokens and records in mContext table.
 *      so that we can use macros when we are tokenlizing target source file.
 * Returns :
 *      Macro object that parsed from lxTokenlizeMacro.
 */
Macro* Lexer::lxTokenlizeNextMacro()
{
    noway_assert(ttIsSharp(lxGetPrivChar()), "Cannot extract macro type from string!");

    std::string              macroToken;
    std::vector<std::string> macroOperands;

    while (lxIsEOF())
    {
        char c = lxConsumeAndGetChar();
        if (!ttIsSpace(c))
        {
            if (!ttIsAlphabet(c))
            {
                // TODO : unknown charactor indicator.
            }
            macroToken += c;
            continue;
        }
        break;
    }

    // This is for include keyword.
    lxApplyChange();

    if (macroToken == MacroKeyword::MK_INCLUDE)
    {
        bool        isLocalPath = false;
        std::string includePath = lxGetNextFilenameFromInclude(isLocalPath);

        if (isLocalPath)
        {
            return AllocateMacro(MacroType::MACRO_INCLUDE_LOCAL, includePath);
        }
        else
        {
            return AllocateMacro(MacroType::MACRO_INCLUDE_GLOBAL, includePath);
        }
    }
    else
    {
        // You'll need to handle `,` `)` `(` tokens if its define macro.
        bool isDefineMacro = (macroToken == MacroKeyword::MK_DEFINE);
        bool isIfMacro     = (macroToken == MacroKeyword::MK_IF);

        // We have to parse operands for other macros except include and define macro
        // So parsing operands now and it will be used on macros that uses extra operands.
        std::string tempOperand;

        bool hasBackSlash = false;
        while (lxIsEOF())
        {
            char c = lxConsumeAndGetChar();

            if (ttIsSpace(c))
            {
                if (!tempOperand.empty())
                {
                    macroOperands.push_back(tempOperand);
                }
            }

            // Define macro can have parens and comma (for function like macros)
            // Handle it if its define macro
            if (isDefineMacro)
            {
                if (ttIsComma(c) | ttIsParen(c, false) | ttIsParen(c, true))
                {
                    if (!tempOperand.empty())
                    {
                        macroOperands.push_back(tempOperand);
                    }
                    macroOperands.push_back(std::string(&c, 1));
                }
            }

            // If macro can have `!` operator
            // Handle it if its If macro
            if (isIfMacro)
            {
                if (ttIsNotSym(c))
                {
                    if (!tempOperand.empty())
                    {
                        macroOperands.push_back(tempOperand);
                    }
                    macroOperands.push_back(std::string(&c, 1));
                }
            }

            if (ttIsBackSlash(c))
            {
                hasBackSlash = true;
            }

            if (ttIsNextLine(c))
            {
                if (hasBackSlash)
                {
                    if (!ttIsBackSlash(lxGetPrivChar()))
                    {
                        // Emit warning.
                    }

                    hasBackSlash = false;
                    continue;
                }

                break;
            }
        }
    }

    // Apply change that parsed macro token.
    // not to make troble on other parsing or lexing section.
    lxApplyChange();

    // Start identifying macro types except include. include token will be handled specally
    if (macroToken == MacroKeyword::MK_DEFINE)
    {
    }
    else if (macroToken == MacroKeyword::MK_UNDEF)
    {
        if (macroOperands.size() > 1)
        {
            // Emit warning.
        }
        return AllocateMacro(MacroType::MACRO_UNDEF, macroOperands[0]);
    }
    else if (macroToken == MacroKeyword::MK_IF)
    {
        if (macroOperands.size() > 3)
        {
            // Emit warning.
        }

        if (macroOperands.size() == 3)
        {
            if (macroOperands[0] == "!")
            {
                if (macroOperands[1] == MacroKeyword::MK_DEFINED)
                {
                    return AllocateMacro(MacroType::MACRO_IF_NOT_DEF, macroOperands[2]);
                }
                else
                {
                    return AllocateMacro(MacroType::MACRO_IF_DEF, macroOperands[1]);
                }
            }

            // Emit warning.
        }

        if (macroOperands.size() == 2)
        {
            if (macroOperands[0] == MacroKeyword::MK_DEFINED)
            {
                return AllocateMacro(MacroType::MACRO_IF_DEF, macroOperands[1]);
            }

            // Emit warning.
        }

        return AllocateMacro(MacroType::MACRO_IF, macroOperands[0]);
    }
    else if (macroToken == MacroKeyword::MK_ELSE)
    {
        if (macroOperands.size() > 0)
        {
            // Emit warning.
        }

        return AllocateMacro(MacroType::MACRO_ELSE);
    }
    else if (macroToken == MacroKeyword::MK_ELSE_IF)
    {
        if (macroOperands.size() > 1)
        {
            // Emit Warning
        }

        return AllocateMacro(MacroType::MACRO_ELSE_IF, macroOperands[0]);
    }
    else if (macroToken == MacroKeyword::MK_IF_DEF)
    {
        if (macroOperands.size() > 1)
        {
            // Emit Warning
        }

        return AllocateMacro(MacroType::MACRO_IF_DEF, macroOperands[0]);
    }
    else if (macroToken == MacroKeyword::MK_IF_NOT_DEF)
    {
        if (macroOperands.size() > 1)
        {
            // Emit Warning
        }

        return AllocateMacro(MacroType::MACRO_IF_NOT_DEF, macroOperands[0]);
    }
    else if (macroToken == MacroKeyword::MK_END_IF)
    {
        return AllocateMacro(MacroType::MACRO_END_IF);
    }

    return nullptr;
}

} // namespace C
} // namespace Language
} // namespace Goto