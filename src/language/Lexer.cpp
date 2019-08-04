#include "basic/Debug.h"

#include "language/Lexer.h"
#include "language/TokenVerifier.h"


namespace Goto
{
    namespace Language
    {
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

        Token* TokenContext::CreateUnknownToken(char token)
        {
            m_tcUnknownTokenCnt++;
            return nullptr;
        }

        Token* TokenContext::CreateLiteralToken(char* token, size_t length)
        {
            m_tcLiteralTokenCnt++;
            return nullptr;
        }

        Token* TokenContext::CreateSymbolToken(char token)
        {
            m_tcSymbolTokenCnt++;
            return nullptr;
        }

        Token* TokenContext::CreateIdentifierToken(char* token, size_t length)
        {
            m_tcIdentifierTokenCnt++;
            return nullptr;
        }

        Token* TokenContext::CreateWhitespaceToken(size_t whitespaceLength)
        {
            m_tcWhitespaceTokenCnt++;
            return nullptr;
        }

        void TokenContext::InsertToken(Token* nextToken)
        {
        }

        constexpr size_t TokenContext::GetTokenObjectSize()
        {
            return sizeof(Token) + 32;
        }

        //
        // Lexer implements section.
        //

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
        }

        void lxSkipSpaces(const char* srcFileBuf, size_t srcFileLen, size_t& index)
        {
            noway_assert(tvIsSpace(srcFileBuf[index]), "Cannot skip spaces, target charactor is not space!");

            for (; index < srcFileLen; ++index)
            {
                if (!tvIsSpace(srcFileBuf[index]))
                {
                    break;
                }
            }
        }

        /* lxGetIdentifierOnScope
         *
         * Description :
         *      Parse string that is not a specal symbols
         * Params :
         *      - srcFileBuf : target source file buffer
         *      - srcFileLen : target source file length
         *      - index : current reading index
         * Returns :
         *      return parsed identifier string
         */
        std::string lxGetIdentifierOnScope(const char* srcFileBuf, size_t srcFileLen, size_t& index)
        {
            noway_assert(tvIsSpecalSym(srcFileBuf[index]), "Identifier should not start with specal symbols!");

            std::string identifier;
            for (index; index < srcFileLen; ++index)
            {
                char c = srcFileBuf[index];

                if (tvIsSpecalSym(c))
                {
                    break;
                }
                identifier += c;
            }

            index--;
            return identifier;
        }

         /* lxGetStringLiteralOnScope
          *
          * Description:
          *     Parse string that contains in literal, which is ' or "
          * Params :
          *      - srcFileBuf : target source file buffer
          *      - srcFileLen : target source file length
          *      - index : curret reading index
          * Returns :
          *     return parsed string of literal
          */
        std::string lxGetStringLiteralOnScope(const char* srcFileBuf, size_t srcFileLen, size_t& index)
        {
            noway_assert(tvIsDoubleQuote(srcFileBuf[index++]), "Cannot extract string from string literal!");
            std::string literal;

            for (; index < srcFileLen; ++index)
            {
                char c = srcFileBuf[index];

                literal += c;
                if (tvIsDoubleQuote(c))
                {
                    break;
                }
            }
            
            return literal;
        }

        /* lxTokenlizeMacro
         *
         * Description:
         *     Parse filename from include macro
         * Params :
         *      - srcFileBuf : target source file buffer
         *      - srcFileLen : target source file length
         *      - index : curret reading index
         *      - isLocalPath : is filename on local path.
         * Returns :
         *     Filename that include macro contains.
         */
        std::string lxGetFilenameFromInclude(const char* srcFileBuf, size_t srcFileLen, size_t& index, bool& isLocalPath)
        {
            const char initialC = srcFileBuf[index++];
            noway_assert(tvIsSpace(initialC) || tvIsDoubleQuote(initialC) || tvIsLessThanSym(initialC), 
                "Cannot extract include path from string!");

            std::string fileName;

            bool startRecord = false;
            for (; index < srcFileLen; ++index)
            {
                char c = srcFileBuf[index];

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
                    fileName = lxGetStringLiteralOnScope(srcFileBuf, srcFileLen, index);
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

        /* lxTokenlizeMacro
         *
         * Description:
         *      Parse macro tokens and records in mContext table.
         *      so that we can use macros when we are tokenlizing target source file.
         * Params :
         *      - mContext : context that conatins current parsed macros in this instance
         *      - srcFileBuf : target source file buffer
         *      - srcFileLen : target source file length
         *      - index : curret reading index
         * Returns : 
         *      Macro object that parsed from lxTokenlizeMacro.
         */
        Macro* lxTokenlizeMacro(MacroContext* mContext, const char* srcFileBuf, size_t srcFileLen, size_t& index)
        {
            noway_assert(tvIsSharp(srcFileBuf[index++]), "Cannot extract macro type from string!");

            Macro*      macro;
            std::string macroToken;

            for (; index < srcFileLen; ++index)
            {
                char c = srcFileBuf[index];
                if (!tvIsSpace(c))
                {
                    if (!tvIsAlphabet(c))
                    {
                        // TODO : unknown charactor indicator.
                    }
                    macroToken += c;
                }
                break;
            }

            // Start identifying macro types.
            if (macroToken == MacroKeyword::MK_DEFINE)
            {

            }
            else if (macroToken == MacroKeyword::MK_UNDEF)
            {
                lxSkipSpaces(srcFileBuf, srcFileLen, index);
                std::string undefTarget = lxGetIdentifierOnScope(srcFileBuf, srcFileLen, index);
            }
            else if (macroToken == MacroKeyword::MK_IF)
            {

            }
            else if (macroToken == MacroKeyword::MK_ELSE)
            {

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

            }
            else if (macroToken == MacroKeyword::MK_INCLUDE)
            {
                bool        isLocalPath = false;
                std::string includePath = lxGetFilenameFromInclude(srcFileBuf, srcFileLen, index, isLocalPath);
            }

            return macro;
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
            for (size_t index = 0; index < srcFileLen; ++index)
            {
                const char c = srcFileBuf[index];
                if (tvIsSharp(c)) 
                {
                    Macro* newMacro = lxTokenlizeMacro(mContext, srcFileBuf, srcFileLen, index);
                }

                switch (c)
                {
                case TK_SPACE:
                    continue;
                case TK_DOUBLE_QUOTE:
                    {
                        std::string stringLiteral = lxGetStringLiteralOnScope(srcFileBuf, srcFileLen, index);
                    }
                    break;
                }
            }
            return false;
        }
        


    } // namespace Language
} // namespace Goto