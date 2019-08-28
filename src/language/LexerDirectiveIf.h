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
};

enum class UnaryOpType
{
};

class IfExprUnaryOp : public IfExpr
{
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