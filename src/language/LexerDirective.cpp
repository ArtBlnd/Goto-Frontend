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
    if (keyword == "define")
    {
        return DirectiveType::DT_DEFINE;
    }
    else if (keyword == "error")
    {
        return DirectiveType::DT_ERROR;
    }
    else if (keyword == "undef")
    {
        return DirectiveType::DT_UNDEF;
    }
    else if (keyword == "elif")
    {
        return DirectiveType::DT_ELSE_IF;
    }
    else if (keyword == "if")
    {
        return DirectiveType::DT_IF;
    }
    else if (keyword == "include")
    {
        return DirectiveType::DT_INCLUDE;
    }
    else if (keyword == "else")
    {
        return DirectiveType::DT_ELSE;
    }
    else if (keyword == "ifdef")
    {
        return DirectiveType::DT_IFDEF;
    }
    else if (keyword == "ifndef")
    {
        return DirectiveType::DT_IFNDEF;
    }
    else if (keyword == "pragma")
    {
        return DirectiveType::DT_PRAGMA;
    }

    return DirectiveType::DT_UNKNOWN;
}

Directive* ParseDirectiveDefine(Lexer* lexer)
{
    return nullptr;
}

Directive* ParseDirectiveInclude(Lexer* lexer)
{
    return nullptr;
}

Directive* ParseDirectiveNoOp(Lexer* lexer, DirectiveType type)
{
    noway_assert(type == DirectiveType::DT_ELSE | type == DirectiveType::DT_ENDIF, "Invalid DirectiveNoOp type!");

    // Else, Endif Directives
    //
    // #else line-end
    // #endif line-end
    return lexer->GetLexerContext()->AllocDirectiveNoOp(type);
}

Directive* ParseDirectiveOp1(Lexer* lexer, DirectiveType type)
{
    LexerContext* lexerContext = lexer->GetLexerContext();

    // Skipping space that exists between directive type token and first operand.
    lexer->lxSkipSpace(true);
    noway_assert(!ttIsSpace(lexer->lxGetCurrChar()), "Starting charactor of first operands cannot be space!");

    // Error Directive
    //
    // #error token-string line-end
    // We have to parse it before its end-line
    if (type == DirectiveType::DT_ERROR)
    {
        std::string ErrorStr = lexer->lxParseStringBeforeEnd(ttIsNextLine);
        return lexerContext->AllocDirectiveOp1(type, ErrorStr);
    }

    // Undef, Ifdef, Ifndef Directives
    //
    // #undef identifier line-end
    // #ifdef identifier line-end
    // #ifndef identifier line-end
    std::string Op1 = lexer->lxParseStringBeforeEnd([](char c) {
        if (ttIsSpace(c) | ttIsNextLine(c))
        {
            return true;
        }
        return false;
    });

    return lexerContext->AllocDirectiveOp1(type, Op1);
}

Directive* ParseDirectiveOp2(Lexer* lexer, DirectiveType type)
{
    return nullptr;
}

Directive* ParseDirectiveIf(Lexer* lexer, DirectiveType type)
{
    return nullptr;
}

Directive* ParseDirectivePragma(Lexer* lexer, DirectiveType type)
{
    return nullptr;
}

Directive* ParseDriectiveFrom(Lexer* lexer)
{
    Directive* newDirective = nullptr;

    noway_assert(ttIsSharp(lexer->lxConsumeAndGetChar()), "directive cannot start without # token!");
    std::string driectiveKeyword = lexer->lxParseStringBeforeEnd(ttInverse(ttIsAlphabet));

    DirectiveType type = TransformKeywordToDrirectiveType(driectiveKeyword);
    switch (type)
    {
        case DirectiveType::DT_DEFINE:
            newDirective = ParseDirectiveDefine(lexer);
            break;

        case DirectiveType::DT_INCLUDE:
            newDirective = ParseDirectiveInclude(lexer);
            break;

        case DirectiveType::DT_ELSE:
        case DirectiveType::DT_ENDIF:
            newDirective = ParseDirectiveNoOp(lexer, type);
            break;

        case DirectiveType::DT_ELSE_IF:
        case DirectiveType::DT_IF:
            newDirective = ParseDirectiveIf(lexer, type);
            break;

        case DirectiveType::DT_ERROR:
        case DirectiveType::DT_IFDEF:
        case DirectiveType::DT_IFNDEF:
        case DirectiveType::DT_UNDEF:
            newDirective = ParseDirectiveOp1(lexer, type);
            break;

        case DirectiveType::DT_LINE:
            newDirective = ParseDirectiveOp2(lexer, type);
            break;

        case DirectiveType::DT_PRAGMA:
            newDirective = ParseDirectivePragma(lexer, type);
            break;

        case DirectiveType::DT_UNKNOWN:
            break;

        default:
            // define keyword will be handled specally.
            noway_assert(false, "Invalid directive type!");
    }

    return newDirective;
}

void HandleIncludeDirective(Directive* directive, LexerContext* lexer) {}

void HandleDefineDirective(Directive* directive, LexerContext* lexer, bool isFuncLike) {}

void HandleConditionalDirective(Directive* directive, LexerContext* lexer) {}

} // namespace Language
} // namespace Goto