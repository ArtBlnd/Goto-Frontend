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
    virtual int64_t Evaluate(Lexer* lexer) = 0;
};

class IfExprIdentifier : public IfExpr
{
    const std::string Identifier;

public:
    IfExprIdentifier() = delete;
    IfExprIdentifier(std::string identifier);

    int64_t Evaluate(Lexer* lexer) override;

    const std::string GetIdentifier() const;
};

enum class UnaryOpTypes
{
    PLUS_OP        = 0x01, // +Expr
    MINUS_OP       = 0x02, // -Expr
    DEFINED_OP     = 0x03, // defined(Expr)
    LOGICAL_NOT_OP = 0x04, // !Expr
    BITWISE_NOT_OP = 0x05, // ~Expr
};

class IfExprUnaryOp : public IfExpr
{
    UnaryOpTypes uoType;
    IfExpr*      uoExpr;

public:
    IfExprUnaryOp() = delete;
    IfExprUnaryOp(UnaryOpTypes type, IfExpr* expr);

    int64_t Evaluate(Lexer* lexer) override;
};

enum class BinaryOpTypes
{
    PLUS_OP        = 0x01, // LHS + RHS
    MINUS_OP       = 0x02, // LHS - RHS
    MULTIPLY_OP    = 0x03, // LHS * RHS
    DIVIDE_OP      = 0x04, // LHS / RHS
    BITWISE_AND    = 0x05, // LHS & RHS
    BITWISE_OR     = 0x06, // LHS | RHS
    LOGICAL_AND_OP = 0x07, // LHS && RHS
    LOGICAL_OR_OP  = 0x08, // LHS || RHS
    COMPARE_EQ     = 0x09, // LHS == RHS
    COMPARE_NE     = 0x0A, // LHS != RHS
    COMPARE_LT     = 0x0B, // LHS < RHS
    COMPARE_LE     = 0x0C, // LHS <= RHS
    COMPARE_GT     = 0x0D, // LHS > RHS
    COMPARE_GE     = 0x0E, // LHS >= RHS
    XOR_OP         = 0x0F, // LHS ^ RHS
    LSHIFT_OP      = 0x10, // LHS << RHS
    RSHIFT_OP      = 0x11, // LHS >> RHS
};

class IfExprBinaryOp : public IfExpr
{
    BinaryOpTypes boType;
    IfExpr*       boExprL;
    IfExpr*       boExprR;

public:
    IfExprBinaryOp() = delete;
    IfExprBinaryOp(BinaryOpTypes type, IfExpr* op1, IfExpr* op2);

    int64_t Evaluate(Lexer* lexer) override;
};

class IfExprConstant : public IfExpr
{
    int64_t Constant;

public:
    IfExprConstant() = delete;
    IfExprConstant(int64_t constant);

    int64_t Evaluate(Lexer* lexer) override;
};

int64_t EvaluateIfExpr(Lexer* lexer, std::string Expr);

} // namespace Language
} // namespace Goto

#endif