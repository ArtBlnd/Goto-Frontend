#ifndef __GOTO_FRONTEND_LANGUAGE_LEXER_DIRECTIVE_IF_H__
#define __GOTO_FRONTEND_LANGUAGE_LEXER_DIRECTIVE_IF_H__

#include <string>

namespace Goto
{
namespace Language
{
class LexerContext;
class Lexer;

class IfExpr
{
public:
    virtual uint64_t Evaluate(Lexer* lexer) = 0;
};

class IfExprIdentifier : public IfExpr
{
    const std::string Identifier;

public:
    IfExprIdentifier() = delete;
    IfExprIdentifier(std::string identifier);

    uint64_t Evaluate(Lexer* lexer) override;

    const std::string GetIdentifier() const;
};

enum class UnaryOpType
{
    PLUS_OP        = 0x01, // +
    MINUS_OP       = 0x02, // -
    DEFINED_OP     = 0x03, // defined(Expr)
    LOGICAL_NOT_OP = 0x04, // !
    BITWISE_NOT_OP = 0x05, // ~
};

class IfExprUnaryOp : public IfExpr
{
    UnaryOpType uoType;
    IfExpr*     uoExpr;

public:
    IfExprUnaryOp() = delete;
    IfExprUnaryOp(UnaryOpType type, IfExpr* expr);

    uint64_t Evaluate(Lexer* lexer) override;
};

class IfExprBinaryOp : public IfExpr
{
};

class IfExprConstant : public IfExpr
{
};

class IfExprScope : public IfExpr
{
};

uint64_t EvaluateIfExpr(Lexer* lexer);

} // namespace Language
} // namespace Goto

#endif