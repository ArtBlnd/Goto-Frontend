#include "basic/Debug.h"

#include "language/TokenVerifier.h"
#include "language/C/Lexer.h"

namespace Goto
{
namespace Language
{
namespace C
{
    inline bool IsSpecalSym(const char c)
    {
        return tvIsColon(c)         | // :
            tvIsSemicolon(c)        | // ;
            tvIsEqualSym(c)         | // =
            tvIsComma(c)            | // ,
            tvIsDot(c)              | // .
            tvIsAsterisk(c)         | // *
            tvIsSharp(c)            | // #
            tvIsPlusSym(c)          | // +
            tvIsMinusSym(c)         | // -
            tvIsNotSym(c)           | // !
            tvIsXorSym(c)           | // ^
            tvIsModSym(c)           | // %
            tvIsAndSym(c)           | // &
            tvIsAtSym(c)            | // @
            tvIsBracket(c, true)    | // {
            tvIsBracket(c, false)   | // }
            tvIsParen(c, true)      | // (
            tvIsParen(c, false)     | // )
            tvIsGreaterThanSym(c)   | // >
            tvIsLessThanSym(c);       // <
    }

    inline bool IsSeperator(const char c)
    {
        return tvIsColon(c)         | // :
            tvIsSpace(c)            | // 
            tvIsNextLine(c)         | // \n
            tvIsSemicolon(c)        | // ;
            tvIsEqualSym(c)         | // =
            tvIsComma(c)            | // ,
            tvIsDot(c)              | // .
            tvIsAsterisk(c)         | // *
            tvIsSharp(c)            | // #
            tvIsPlusSym(c)          | // +
            tvIsMinusSym(c)         | // -
            tvIsNotSym(c)           | // !
            tvIsXorSym(c)           | // ^
            tvIsModSym(c)           | // %
            tvIsAndSym(c)           | // &
            tvIsAtSym(c)            | // @
            tvIsBracket(c, true)    | // {
            tvIsBracket(c, false)   | // }
            tvIsParen(c, true)      | // (
            tvIsParen(c, false)     | // )
            tvIsGreaterThanSym(c)   | // >
            tvIsLessThanSym(c);       // <
    }

    // ============================================
    // Token Implements
    // ============================================

    Token::Token(TokenType Type, size_t Size, size_t Line, size_t Column)
    {
        m_tkType = Type;
        m_tkSize = Size;
        m_tkLine = Line;
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

    TokenUnknown::TokenUnknown(size_t Line, size_t Column, char UnknownToken) :
        Token(TokenType::TOKEN_UNKNOWN, 1 /* One Char */, Line, Column)
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

    TokenLiteral::TokenLiteral(size_t Line, size_t Column, std::string SymbolLiteral) :
        Token(TokenType::TOKEN_LITERAL, SymbolLiteral.length(), Line, Column)
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

    TokenSymbol::TokenSymbol(size_t Line, size_t Column, char SymbolToken) :
        Token(TokenType::TOKEN_SYMBOL, 1 /* One Char */, Line, Column)
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
        return tvIsParen(Get(), isClosed);
    }

    bool TokenSymbol::IsSymbolSquare(bool isClosed) const
    {
        return tvIsSquare(Get(), isClosed);
    }

    bool TokenSymbol::IsSymbolCurly(bool isClosed) const
    {
        return tvIsBracket(Get(), isClosed);
    }

    bool TokenSymbol::IsSymbolSemicolon() const
    {
        return tvIsSemicolon(Get());
    }

    bool TokenSymbol::IsSymbolAsterisk() const
    {
        return tvIsAsterisk(Get());
    }

    // ============================================
    // Token Identifier Implements
    // ============================================

    TokenIdentifier::TokenIdentifier(size_t Line, size_t Column, std::string IdentifierToken) :
        Token(TokenType::TOKEN_IDENTIFIER, IdentifierToken.size(), Line, Column)
    {
        m_tkIdentifier = IdentifierToken;
    }

    // ============================================
    // Token Whitespace Implements
    // ============================================

    TokenWhitespace::TokenWhitespace(size_t Size, size_t Line, size_t Column) :
        Token(TokenType::TOKEN_WHITESPACE, Size, Line, Column)
    {

    }

    // ============================================
    // TokenContext Implements
    // ============================================
    void TokenContext::InsertToken(Token* nextToken)
    {
    }

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

    MacroType Macro::GetMacroType() const
    {
        return m_mcrType;
    }

    // ============================================
    // Lexer implements section.
    // ============================================

    // Macro keyword token table.
    namespace MacroKeyword
    {
        const std::string MK_DEFINE = "define";
        const std::string MK_UNDEF = "undef";
        const std::string MK_IF = "if";
        const std::string MK_ELSE = "else";
        const std::string MK_ELSE_IF = "elif";
        const std::string MK_IF_DEF = "ifdef";
        const std::string MK_IF_NOT_DEF = "ifndef";
        const std::string MK_END_IF = "endif";
        const std::string MK_DEFINED = "defined";
        const std::string MK_INCLUDE = "include";
    }

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
        : lxTokenContext(tContext), lxMacroContext(mContext), lxSrcFileBuf(srcFileBuf), lxSrcFileLen(srcFileLen)
    {
        noway_assert(lxTokenContext, "Token context cannot be nullptr!");
        noway_assert(lxMacroContext, "Macro context cannot be nullptr!");
        noway_assert(lxSrcFileBuf, "Source file buffer cannot be nullptr!");
        noway_assert(lxSrcFileLen, "Source file length cannot be zero!");
    }

    bool Lexer::IsEOF() const
    {
        if (lxIndex == lxSrcFileLen)
        {
            return true;
        }

        return false;
    }

    char Lexer::ConsumeChar()
    {
        char c = lxSrcFileBuf[lxIndex++];

        if (tvIsNextLine(c))
        {
            lxCurrentColmn = 0;
            lxCurrentLine++;
        }
        else
        {
            lxCurrentColmn++;
        }

        return c;
    }

    void Lexer::UngetChar()
    {
        lxIndex--;

        if (tvIsNextLine(GetCurrentChar()))
        {
            for (size_t index = lxIndex; tvIsNextLine(lxSrcFileBuf[index]); index--)
            {
                lxCurrentColmn++;
                noway_assert(index > 0);
            }

            lxCurrentLine--;
        }
        else
        {
            lxCurrentColmn--;
        }
    }

    char Lexer::GetCurrentChar()
    {
        return lxSrcFileBuf[lxIndex];
    }

    bool Lexer::lxStartTokenlizeSourceCode()
    {
        while (IsEOF())
        {
            const char c = ConsumeChar();
            if (tvIsSharp(c))
            {
                Macro* newMacro = lxTokenlizeNextMacro();
            }

            switch (c)
            {
            case TK_SPACE:
                continue;
            case TK_DOUBLE_QUOTE:
            {
                std::string stringLiteral = lxGetNextStringLiteralOnScope();
            }
            break;
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
        noway_assert(tvIsSpecalSym(ConsumeChar()), "Identifier should not start with specal symbols!");

        std::string identifier;
        while (IsEOF())
        {
            char c = ConsumeChar();

            if (IsSpecalSym(c))
            {
                break;
            }
            identifier += c;
        }

        UngetChar();
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
        noway_assert(tvIsDoubleQuote(ConsumeChar()), "Cannot extract string from string literal!");
        std::string literal;

        while (IsEOF())
        {
            char c = ConsumeChar();

            literal += c;
            if (tvIsDoubleQuote(c))
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
        const char initialC = ConsumeChar();
        noway_assert(tvIsSpace(initialC) || tvIsDoubleQuote(initialC) || tvIsLessThanSym(initialC),
            "Cannot extract include path from string!");

        std::string fileName;

        bool startRecord = false;
        while (IsEOF())
        {
            char c = ConsumeChar();

            if (startRecord)
            {
                fileName += c;
                if (tvIsGreaterThanSym(c))
                {
                    break;
                }
            }

            // We are skipping space that in between < or " and end of `e` which is end of include token
            if (tvIsSpace(c))
            {
                continue;
            }

            // Start parsig "`string`"
            if (tvIsDoubleQuote(c))
            {
                fileName = lxGetNextStringLiteralOnScope();
                isLocalPath = true;
                break;
            }

            // Start parsing <`string`>
            if (tvIsLessThanSym(c))
            {
                isLocalPath = false;
                startRecord = true;
            }

            // TODO : replace assert to source trace.
            noway_assert(true, "[INTERNAL] failed to find start of define token");
        }

        return fileName;
    }

    std::string Lexer::lxTokenlizeNextMacroOperands()
    {
        std::string macroOperand;

        bool isBackSlashFound = false;
        while (IsEOF())
        {
            char c = ConsumeChar();
            if (!tvIsNextLine(c))
            {
                if (tvIsBackSlash(c))
                {
                    isBackSlashFound = true;
                }

                macroOperand += c;
                continue;
            }

            if (isBackSlashFound)
            {
                isBackSlashFound = false;
                continue;
            }

            break;
        }

        return macroOperand;
    }

    /* lxTokenlizeMacro
     *
     * Description:
     *      Parse macro tokens and records in mContext table.
     *      so that we can use macros when we are tokenlizing target source file.
     * Returns :
     *      Macro object that parsed from lxTokenlizeMacro.
     */
    Macro* Lexer::lxTokenlizeNextMacro(bool skipSharpCheck)
    {
        if (!skipSharpCheck)
        {
            noway_assert(tvIsSharp(srcFileBuf[index++]), "Cannot extract macro type from string!");
        }

        std::string macroToken;


        while (IsEOF())
        {
            char c = ConsumeChar();
            if (!tvIsSpace(c))
            {
                if (!tvIsAlphabet(c))
                {
                    // TODO : unknown charactor indicator.
                }
                macroToken += c;
                continue;
            }
            break;
        }

        // Start identifying macro types.
        if (macroToken == MacroKeyword::MK_DEFINE)
        {

        }
        else if (macroToken == MacroKeyword::MK_UNDEF)
        {
            lxSkipSpaces();
            return AllocateMacro(MacroType::MACRO_UNDEF, lxGetNextIdentifierOnScope());
        }
        else if (macroToken == MacroKeyword::MK_IF)
        {

        }
        else if (macroToken == MacroKeyword::MK_ELSE)
        {
            return AllocateMacro(MacroType::MACRO_ELSE);
        }
        else if (macroToken == MacroKeyword::MK_ELSE_IF)
        {

        }
        else if (macroToken == MacroKeyword::MK_IF_DEF)
        {

        }
        else if (macroToken == MacroKeyword::MK_IF_NOT_DEF)
        {

        }
        else if (macroToken == MacroKeyword::MK_END_IF)
        {

        }
        else if (macroToken == MacroKeyword::MK_DEFINED)
        {
            lxSkipSpaces();
            return AllocateMacro(MacroType::MACRO_DEFINED, lxGetNextIdentifierOnScope());
        }
        else if (macroToken == MacroKeyword::MK_INCLUDE)
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

        return nullptr;
    }

}
} // namespace Language
} // namespace Goto