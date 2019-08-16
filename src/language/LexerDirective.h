#ifndef __GOTO_FRONTEND_LANGUAGE_LEXER_DIRECTIVE_H__
#define __GOTO_FRONTEND_LANGUAGE_LEXER_DIRECTIVE_H__

#include <string>
#include <vector>

namespace Goto
{
namespace Language
{
class Lexer;
class LexerContext;

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
    DF_OP2         = 0x03,
    DF_FUNC_DEFINE = 0x04,
    DF_PRAGMA      = 0x05,

    DF_UNKNOWN = 0xFF
};

class DirectiveNoOp;
class DirectiveOp1;
class DirectiveOp2;
class DirectiveDefine;
class DirectivePragma;
class Directive
{
    size_t dtId = (size_t)(-1);

    DirectiveType dtType = DirectiveType::DT_UNKNOWN;
    DirectiveFunc dtFunc = DirectiveFunc::DF_UNKNOWN;

protected:
    Directive() = delete;
    Directive(DirectiveType type, DirectiveFunc func, size_t id);
    Directive(DirectiveType type, DirectiveFunc func);

public:
    DirectiveType GetType() const;
    DirectiveFunc GetFunc() const;

    DirectiveNoOp* AsDirectiveNoOp();
    bool           IsDirectiveNoOp() const;

    DirectiveOp1* AsDirectiveOp1();
    bool          IsDirectiveOp1() const;

    DirectiveOp2* AsDirectiveOp2();
    bool          IsDirectiveOp2() const;

    DirectiveFuncDefine* AsDirectiveFuncDefine();
    bool                 IsDirectiveFuncDefine() const;

    DirectivePragma* AsDirectivePragma();
    bool             IsDirectivePragma() const;

    // This is used for check that directive is same directive when its caching.
    // The id should same when recording resolved expression on directive cache
    size_t GetID() const;
};

class DirectiveNoOp : public Directive
{
    // Handling it as directive itself.
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
    const std::string& GetOp1();
    const std::string& GetOp2();
};

class DirectiveFuncDefine : public Directive
{
    std::string              Expr;
    std::vector<std::string> Params;

public:
    size_t GetParamSize() const;

    const std::string& GetExpr();
    const std::string& GetParamName(size_t index);

    bool ResolveDefineExpr(std::string Name, const std::vector<std::string>& Params);
};

class DirectiveIfStmt : public Directive
{
    std::string Expr;

public:
    const std::string& GetExpr();

    bool ResolveIfStmt();
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