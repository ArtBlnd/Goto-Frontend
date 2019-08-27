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
};

class IfExprIdentifier
{
};

class IfExprUnaryOp
{
};

class IfExprBinaryOp
{
};

class IfExprScope
{
};

uint64_t EvaluateIfExpr(Lexer* lexer);

} // namespace Language
} // namespace Goto

#endif