#ifndef __GTFW_C_FRONTEND_PARSER_PARSER_H__
#define __GTFW_C_FRONTNED_PARSER_PARSER_H__

namespace GTFW
{
    namespace Parser
    {
        class TokenUnknown;
        class TokenLiteral;
        class TokenSymbol;
        class TokenIdentifier;

        enum class TokenType
        {
            TOKEN_UNKNOWN       = 0xFF,
            TOKEN_LITERAL       = 0x01,
            TOKEN_SYMBOL        = 0x02,
            TOKEN_IDENTIFIER    = 0x03,
        };

        // class Token
        // Information :
        //      Base class of all token objects
        //      contains basic information of token object, such as size, line, colum, type.
        class Token
        {
            TokenType m_tkType;
            size_t    m_tkSize;
            size_t    m_tkLine;
            size_t    m_tkColumn;

        protected:
            Token() = delete;
            Token(TokenType Type, size_t Size, size_t Line, size_t Column);

        public:
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
        };

        class TokenUnknown : Token
        {

        };

        class TokenLiteral : Token
        {
            
        public:
            bool IsStringLiteral();
            bool IsFloatingLiteral();
            bool IsIntegerLiteral();
        };

        class TokenSymbol : Token
        {

        public:
            bool IsSymbolParen(bool isClosed);
            bool IsSymbolSquare(bool isClosed);
            bool IsSymbolSemicolon();
            bool IsSymbolAsterisk();
            bool isSymbolCurly(bool isClosed);
        };

        class TokenIdentifier : Token
        {

        };

        // class TokenContext
        // Information:
        //      This contains token informations for parsed tokens
        class TokenContext
        {

        };


    }
}

#endif