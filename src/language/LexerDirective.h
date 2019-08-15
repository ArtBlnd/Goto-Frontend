#ifndef __GOTO_FRONTEND_LANGUAGE_LEXER_DIRECTIVE_H__
#define __GOTO_FRONTEND_LANGUAGE_LEXER_DIRECTIVE_H__

#include <string>

namespace Goto
{
namespace Language
{

enum class DirectiveType
{
    DT_DEFINE  = 0x01,
    DT_ERROR   = 0x02,
    DT_UNDEF   = 0x03,
    DT_ELSE_IF = 0x04,
    DT_IF      = 0x05,
    DT_INCLUDE = 0x06,
    DT_ELSE    = 0x07,
    DT_IFDEF   = 0x08,
    DT_LINE    = 0x09,
    DT_ENDIF   = 0x0A,
    DT_IFNDEF  = 0x0B,
    DT_PRAGMA  = 0x0C,

    DT_UNKNOWN = 0xFF
};

enum class DirectiveFunc
{
    DF_NO_OP       = 0x01,
    DF_OP1         = 0x02,
    DF_FUNC_DEFINE = 0x03,
    DF_PRAGMA      = 0x04,

    DF_UNKNOWN = 0xFF
};

class DirectiveNoOp;
class DirectiveOp1;
class DirectiveOp2;
class DirectiveDefine;
class DirectivePragma;
class Directive
{
    DirectiveType dtType = DirectiveType::DT_UNKNOWN;
    DirectiveFunc dtFunc = DirectiveFunc::DF_UNKNOWN;

public:
    DirectiveType GetType();
    DirectiveFunc GetFunc();

    DirectiveNoOp* AsDirectiveNoOp();
    bool           IsDirectiveNoOp();

    DirectiveOp1* AsDirectiveOp1();
    bool          IsDirectiveOp1();

    DirectiveOp2* AsDirectiveOp2();
    bool          IsDirectiveOp2();

    DirectiveFuncDefine* AsDirectiveFuncDefine();
    bool                 IsDirectiveFuncDefine();

    DirectivePragma* AsDirectivePragma();
    bool             IsDirectivePragma();
};

class DirectiveNoOp : public Directive
{
};

class DirectiveOp1 : public Directive
{
    std::string Op1;

public:
    const std::string& GetOp1();
};

class DirectiveOp2 : public Directive
{
    std::string Op1;
    std::string Op2;

public:
    const std::string& GetOp2();
};

class DirectiveFuncDefine : public Directive
{
    std::string              Expr;
    std::vector<std::string> Params;

public:
    const std::string& GetExpr();
    const std::string& GetParamName(size_t index);

    bool ResolveDefineExpr(std::string Name, const std::vector<std::string>& Params);
    bool ResolveDefineExpr(std::string Name);
};

class DirectivePragma : public Directive
{
};

Directive* ParseDriectiveFrom(Lexer* lexer);
void       HandleIncludeDirective(Directive* directive, LexerContext* lexer);
void       HandleDefineDirective(Directive* directive, LexerContext* lexer, bool isFuncLike);

} // namespace Language
} // namespace Goto

#endif