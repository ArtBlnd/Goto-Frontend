#ifndef __GOTO_C_FROTNEND_LANGUAGE_LEXER_H__
#define __GOTO_C_FRONTEND_LANGUAGE_LEXER_H__

#include <string>

namespace Goto
{
    namespace Engine
    {
        class Engine;
    }

    namespace Language
    {
        class Token;
        class TokenUnknown;
        class TokenLiteral;
        class TokenSymbol;
        class TokenIdentifier;
        class TokenWhitespace;

        enum class MacroType
        {
            MACRO_UNKNOWN       = 0xFF,
            MACRO_DEFINE        = 0x01,
            MACRO_UNDEF         = 0x02,
            MACRO_IF            = 0x03,
            MACRO_ELSE          = 0x04,
            MACRO_ELSE_IF       = 0x05,
            MACRO_IF_DEF        = 0x06,
            MACRO_IF_NOT_DEF    = 0x07,
            MACRO_END_IF        = 0x08,
            MACRO_DEFINED       = 0x09
        };

        class Macro
        {
            MacroType m_mcrType = MacroType::MACRO_UNKNOWN;
            size_t    m_mcrSize = 0;
            size_t    m_mcrLine = 0;
            size_t    m_mcrColumn = 0;

            Token* m_mcrNextToken = nullptr;
            Token* m_mcrPrivToken = nullptr;

        protected:
            Macro() = delete;
            Macro(MacroType type, size_t size, size_t line, size_t column);
            virtual ~Macro() = default;

        public:
            Token* GetNextToken();
            Token* GetPrivToken();
        };

        class MacroContext
        {
            Macro* m_mcMacroStart;
            Macro* m_mcMacroEnd;

        public:
            Macro* GetPredefDate();
            Macro* GetPredefFile();
            Macro* GetPredefLine(Token* targetToken);
            Macro* GetPredefTime();
        };

        enum class TokenType
        {
            TOKEN_UNKNOWN       = 0xFF,
            TOKEN_LITERAL       = 0x01,
            TOKEN_SYMBOL        = 0x02,
            TOKEN_IDENTIFIER    = 0x03,
            TOKEN_WHITESPACE    = 0x04
        };

        // class Token
        // Information :
        //      Base class of all token objects
        //      contains basic information of token object, such as size, line, colum, type.
        class Token
        {
            TokenType m_tkType = TokenType::TOKEN_UNKNOWN;
            size_t    m_tkSize = 0;
            size_t    m_tkLine = 0;
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
            bool IsTypeOf(TokenType type) const;

            bool IsUnknownType() const;
            TokenUnknown* AsUnknown();

            bool IsLiteralType() const;
            TokenLiteral* AsLiteral();

            bool IsSymbolType() const;
            TokenSymbol* AsSymbol();

            bool IsIdentifierType() const;
            TokenIdentifier* AsIdentifier();

            bool IsWhitesapceType() const;
            TokenWhitespace* AsWhitespace();
        };

        class TokenUnknown : Token
        {
            friend class TokenContext;
            char m_tkUnknown;

        protected:
            TokenUnknown(size_t Line, size_t Column, char UnknownToken);

        public:
            bool IsToken(char token) const;
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
            // 
            // Debugging Informations
            //
            size_t m_tcTotalAllocatedSize = 0;

            size_t m_tcUnknownTokenCnt    = 0;
            size_t m_tcLiteralTokenCnt    = 0;
            size_t m_tcSymbolTokenCnt     = 0;
            size_t m_tcIdentifierTokenCnt = 0;
            size_t m_tcWhitespaceTokenCnt = 0;

            Token* CreateTokenObjectImpl(Engine::Engine* compEngine);

        public:
            Token* CreateUnknownToken(char token);
            Token* CreateLiteralToken(char* token, size_t length);
            Token* CreateSymbolToken(char token);
            Token* CreateIdentifierToken(char* token, size_t length);
            Token* CreateWhitespaceToken(size_t whitespaceLength);

            void InsertToken(Token* nextToken);

            static constexpr size_t GetTokenObjectSize();
        };

        // Tokenlize source code to TokenContext
        bool lxTokenlizeSourceCode(TokenContext* tokenContext, MacroContext* macroContext, const char* srcFileBuf, size_t srcFileLen);
        
        // Compute token to token width
        // for example
        //      void* Func();
        //        ^     ^
        //        |     |
        //        T1    T2
        // returning size of first char 'v' to last T1 char of 'c'. so its 10
        size_t lxComputeT2TWidth(const Token* token1, const Token* token2);

    }
}

#endif