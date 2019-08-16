#include <Basic/Debug.h>
#include <Language/LexerDirective.h>

namespace Goto
{
namespace Language
{

// ============================================================
// Direvtive Implements Section
// ============================================================

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

} // namespace Language
} // namespace Goto