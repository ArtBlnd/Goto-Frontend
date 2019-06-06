#ifndef __GTFW_C_FRONTEND_PARSER_PARSER_H__
#define __GTFW_C_FRONTNED_PARSER_PARSER_H__

#include <string>

namespace GTFW
{
    namespace Parser
    {
        class TokenUnknown;
        class TokenLiteral;
        class TokenSymbol;
        class TokenIdentifier;
        class TokenWhitespace;

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
            TokenUnknown(size_t Line, size_t Column, std::string UnknownToken);

        public:
            bool IsToken(char token) const;
            const char Get() const;
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

            constexpr std::string Get() const;
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

            constexpr char Get() const;
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

        public:
            Token* CreateUnknownToken(char token);
            Token* CreateLiteralToken(char* token, size_t length);
            Token* CreateSymbolToken(char token);
            Token* CreateIdentifierToken(char* token, size_t length);
            Token* CreateWhitespaceToken(size_t whitespaceLength);

            void InsertToken(Token* nextToken);

            static constexpr size_t GetTokenObjectSize();
        };

        // Compute token to token width
        // for example
        //      void* Func();
        //        ^     ^
        //        |     |
        //        T1    T2
        // returning size of first char 'v' to last T1 char of 'c'. so its 10
        size_t psComputeT2TWidth(const Token* token1, const Token* token2);
    }
}

#endif