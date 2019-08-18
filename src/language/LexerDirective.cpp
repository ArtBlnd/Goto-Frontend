#include <Basic/Debug.h>
#include <Language/LexerDirective.h>
#include <Language/Lexer.h>
#include <Language/TokenTable.h>

namespace Goto
{
namespace Language
{

// ============================================================
// Direvtive Implements Section
// ============================================================

Directive::Directive(DirectiveType type, DirectiveFunc func) : dtType(type), dtFunc(func) {}

void Directive::SetId(size_t id)
{
    dtId = id;
}

DirectiveType Directive::GetType() const
{
    return dtType;
}

DirectiveFunc Directive::GetFunc() const
{
    return dtFunc;
}

DirectiveNoOp* Directive::AsDirectiveNoOp()
{
    noway_assert(IsDirectiveNoOp(), "Cannot cast to DirectiveNoOp!");
    return (DirectiveNoOp*)(this);
}

bool Directive::IsDirectiveNoOp() const
{
    return (GetFunc() == DirectiveFunc::DF_NO_OP);
}

DirectiveOp1* Directive::AsDirectiveOp1()
{
    noway_assert(IsDirectiveOp1(), "Cannot cast to DirectiveOp1!");
    return (DirectiveOp1*)(this);
}

bool Directive::IsDirectiveOp1() const
{
    return (GetFunc() == DirectiveFunc::DF_OP1);
}

DirectiveOp2* Directive::AsDirectiveOp2()
{
    noway_assert(IsDirectiveOp2(), "Cannot cast to DirectiveOp2!");
    return (DirectiveOp2*)(this);
}

bool Directive::IsDirectiveOp2() const
{
    return (GetFunc() == DirectiveFunc::DF_OP2);
}

DirectiveFuncDefine* Directive::AsDirectiveFuncDefine()
{
    noway_assert(IsDirectiveFuncDefine(), "Cannot cast to DirectiveFuncDefine!");
    return (DirectiveFuncDefine*)(this);
}

bool Directive::IsDirectiveFuncDefine() const
{
    return (GetFunc() == DirectiveFunc::DF_FUNC_DEFINE);
}

DirectivePragma* Directive::AsDirectivePragma()
{
    noway_assert(IsDirectivePragma(), "Cannot cast to DirectivePragma!");
    return nullptr;
}

bool Directive::IsDirectivePragma() const
{
    return (GetFunc() == DirectiveFunc::DF_PRAGMA);
}

size_t Directive::GetID() const
{
    return dtId;
}

// ============================================================
// DirevtiveNoOp Implements Section
// ============================================================
DirectiveNoOp::DirectiveNoOp(DirectiveType type) : Directive(type, DirectiveFunc::DF_NO_OP)
{
    noway_assert(type == DirectiveType::DT_ELSE | type == DirectiveType::DT_ENDIF, "Invalid DirectiveNoOp type!");
}

// ============================================================
// DirevtiveOp1 Implements Section
// ============================================================
const std::string& DirectiveOp1::GetOp1()
{
    return Op1;
}

// ============================================================
// DirevtiveOp2 Implements Section
// ============================================================
const std::string& DirectiveOp2::GetOp1()
{
    return Op1;
}

const std::string& DirectiveOp2::GetOp2()
{
    return Op2;
}

// ============================================================
// DirevtiveFuncDefine Implements Section
// ============================================================
size_t DirectiveFuncDefine::GetParamSize() const
{
    return Params.size();
}

const std::string& DirectiveFuncDefine::GetExpr() const
{
    return Expr;
}

const std::string& DirectiveFuncDefine::GetParamName(size_t index)
{
    noway_assert(Params.size() < index, "Param index cannot over size of Params");
    return Params[index];
}

bool DirectiveFuncDefine::ResolveDefineExpr(std::string Name, const std::vector<std::string>& Params)
{
    return false;
}

// ============================================================
// DirevtiveIfStmt Implements Section
// ============================================================

const std::string& DirectiveIfStmt::GetExpr() const
{
    return Expr;
}

bool DirectiveIfStmt::ResolveIfStmt()
{
    return false;
}

// ============================================================
// Direvtive Handling Section
// ============================================================

DirectiveType TransformKeywordToDrirectiveType(const std::string& keyword)
{
    if (keyword == "include")
    {
        return DirectiveType::DT_INCLUDE;
    }
    else if (keyword == "define")
    {
        return DirectiveType::DT_DEFINE;
    }
    else if (keyword == "else")
    {
        return DirectiveType::DT_ELSE;
    }
    else if (keyword == "elif")
    {
        return DirectiveType::DT_ELSE_IF;
    }

    return DirectiveType::DT_UNKNOWN;
}

Directive* ParseDirectiveInclude(Lexer* lexer) {}

Directive* ParseDriectiveFrom(Lexer* lexer)
{
    noway_assert(ttIsSharp(lexer->lxConsumeAndGetChar()), "directive cannot start without # token!");
    std::string driectiveKeyword = lexer->lxParseStringBeforeEnd(ttInverse(ttIsAlphabet));

    DirectiveType type = TransformKeywordToDrirectiveType(driectiveKeyword);
    switch (type)
    {
        case DirectiveType::DT_INCLUDE:
            return ParseDirectiveInclude(lexer);
        case DirectiveType::DT_ELSE:

        case DirectiveType::DT_ELSE_IF:
        case DirectiveType::DT_ENDIF:
        case DirectiveType::DT_ERROR:
        case DirectiveType::DT_IFDEF:
        case DirectiveType::DT_IFNDEF:
        case DirectiveType::DT_LINE:
        case DirectiveType::DT_PRAGMA:
        case DirectiveType::DT_UNDEF:

        case DirectiveType::DT_UNKNOWN:
            return nullptr;

        default:
            // define keyword will be handled specally.
            noway_assert(false, "Invalid directive type!");
    }
}

void HandleIncludeDirective(Directive* directive, LexerContext* lexer) {}

void HandleDefineDirective(Directive* directive, LexerContext* lexer, bool isFuncLike) {}

} // namespace Language
} // namespace Goto