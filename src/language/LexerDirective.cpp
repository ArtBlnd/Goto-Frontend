#include <Basic/Debug.h>
#include <Basic/FileUtils.h>

#include <Language/LexerDirective.h>
#include <Language/LexerDirectiveIf.h>
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
    return (DirectivePragma*)(this);
}

bool Directive::IsDirectivePragma() const
{
    return (GetFunc() == DirectiveFunc::DF_PRAGMA);
}

DirectiveIf* Directive::AsDirectiveIf()
{
    noway_assert(IsDirectiveIf(), "Cannot cast to DirectiveIf");
    return (DirectiveIf*)(this);
}

bool Directive::IsDirectiveIf() const
{
    return (GetFunc() == DirectiveFunc::DF_IF);
}

DirectiveInclude* Directive::AsDirectiveInclude()
{
    noway_assert(IsDirectiveInclude(), "Cannot cast to DirectiveInclude");
    return (DirectiveInclude*)(this);
}

bool Directive::IsDirectiveInclude() const
{
    return (GetFunc() == DirectiveFunc::DF_IF);
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
// DirevtiveInclude Implements Section
// ============================================================

DirectiveInclude::DirectiveInclude(std::string path, bool isLocalPath)
    : includePath(std::move(path))
    , isLocal(isLocalPath)
    , Directive(DirectiveType::DT_INCLUDE, DirectiveFunc::DF_INCLUDE)
{
}

bool DirectiveInclude::IsLocalPath() const
{
    return isLocal;
}

const std::string& DirectiveInclude::GetFilePath() const
{
    return includePath;
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

bool IsSpaceOrNextLine(char c)
{
    if (ttIsSpace(c) | ttIsNextLine(c))
    {
        return true;
    }

    return false;
}

Directive* ParseDirectiveDefine(Lexer* lexer)
{
    LexerContext* lexerContext = lexer->GetLexerContext();

    // Skipping space that exists between keyword and identifier.
    lexer->lxSkipSpace();

    std::string defineIdent = lexer->lxParseStringBeforeEnd(ttInverse(ttIsAlphabet));
    if (ttIsParen(lexer->lxGetCurrChar(), false))
    {
        // #define `Identifier`(Params1, ...) `Identifiers...`
        TTFuncA SperatorFunc = [](char c) { return ttIsSpace(c) | ttIsComma(c) | ttIsParen(c, true); };

        std::vector<std::string> ParamIdent;
        std::string              Expr;

        while (lexer->lxIsEOF())
        {
            lexer->lxSkipSpace();

            std::string Param = lexer->lxParseStringBeforeEnd(SperatorFunc);
            if (Param.empty())
            {
                // Emit warning.
            }

            ParamIdent.emplace_back(Param);

            // Skip spaces if end of identifier is space
            // for example. like (Ident1    ,Ident...) or (Ident1   )
            if (ttIsSpace(lexer->lxGetCurrChar()))
            {
                lexer->lxSkipSpace();
            }

            // Check that it has next param Identifier
            // If comma exists next to param identifier. it menas it has next identifier.
            if (ttIsComma(lexer->lxGetCurrChar()))
            {
                lexer->lxConsumeChar();
                continue;
            }

            // End of function like macro definition
            if (ttIsParen(lexer->lxGetCurrChar(), true))
            {
                lexer->lxConsumeChar();
                break;
            }

            return nullptr;
        }

        // Parse expression.
        lexer->lxSkipSpace();
        Expr = lexer->lxParseStringBeforeEnd(ttIsNextLine);

        return lexerContext->AllocDirectiveFuncDefine(std::move(defineIdent), std::move(ParamIdent), std::move(Expr));
    }
    else
    {
        // #define 'Identifier' `Identifiers....`
        lexer->lxSkipSpace();
        std::string Expr = lexer->lxParseStringBeforeEnd(ttIsNextLine);

        return lexerContext->AllocDirectiveOp2(DirectiveType::DT_DEFINE, defineIdent, Expr);
    }

    return nullptr;
}

Directive* ParseDirectiveInclude(Lexer* lexer)
{
    LexerContext* lexerContext = lexer->GetLexerContext();

    // Skipping space that exists between < or " token.
    lexer->lxSkipSpace();

    // Initalize it before changing value because the start of includePath symbol can be invalid.
    std::string includePath = "";
    bool        isLocalPath = false;

    TTFuncA EndFuncComparer;

    // Include Directive.
    if (ttIsLessThanSym(lexer->lxGetCurrChar()))
    {
        EndFuncComparer = [](char c) { return ttIsGreaterThanSym(c) | ttIsNextLine(c); };
        // #include <`includePath`>
    }
    else if (ttIsDoubleQuote(lexer->lxGetCurrChar()))
    {
        isLocalPath     = true;
        EndFuncComparer = [](char c) { return ttIsDoubleQuote(c) | ttIsNextLine(c); };
        // #include "`includePath`"
    }

    lexer->lxConsumeChar();
    includePath = lexer->lxParseStringBeforeEnd(EndFuncComparer);

    // Consume " or > charactor.
    // If \n found. indicate it.
    if (ttIsNextLine(lexer->lxConsumeAndGetChar()))
    {
        // TODO : indicate unknown end of include directive.

        // Returning empty include path.
        // We are not done to parse include path.
        return lexerContext->AllocDirectiveInclude("", isLocalPath);
    }

    return lexerContext->AllocDirectiveInclude(includePath, isLocalPath);
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
    lexer->lxSkipSpace();
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
    std::string Op1 = lexer->lxParseStringBeforeEnd(IsSpaceOrNextLine);
    return lexerContext->AllocDirectiveOp1(type, Op1);
}

Directive* ParseDirectiveOp2(Lexer* lexer, DirectiveType type)
{
    return nullptr;
}

Directive* ParseDirectiveIf(Lexer* lexer, DirectiveType type)
{
    LexerContext* lexerContext = lexer->GetLexerContext();

    lexer->lxSkipSpace();
    std::string Expr = lexer->lxParseStringBeforeEnd(ttIsNextLine);
    lexer->lxSkipSpace();

    return lexerContext->AllocDirectiveIf(EvaluateIfExpr(lexer, Expr) > 0);
}

Directive* ParseDirectivePragma(Lexer* lexer)
{
    return nullptr;
}

Directive* ParseDriectiveFrom(Lexer* lexer)
{
    Directive* newDirective = nullptr;

    noway_assert(ttIsSharp(lexer->lxConsumeAndGetChar()), "directive cannot start without # token!");
    std::string directiveKeyword = lexer->lxParseStringBeforeEnd(ttInverse(ttIsAlphabet));

    if (directiveKeyword.empty())
    {
        // Seems its Null directive.
        return nullptr;
    }

    DirectiveType type = TransformKeywordToDrirectiveType(directiveKeyword);
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
            newDirective = ParseDirectivePragma(lexer);
            break;

        case DirectiveType::DT_UNKNOWN:
            break;

        default:
            // define keyword will be handled specally.
            noway_assert(false, "Invalid directive type!");
    }

    return newDirective;
}

void HandleIncludeDirective(Directive* directive, LexerContext* lexer)
{
    DirectiveInclude* includeDirective = directive->AsDirectiveInclude();

    std::string filePath = includeDirective->GetFilePath();
    if (Basic::fuFileExists(filePath))
    {
        Basic::FileViewer fileView = Basic::FileViewer(includeDirective->GetFilePath());

        if (!Lexer(&fileView, lexer).StartLexSourceCode())
        {
            // TODO : indicate failed to lex source code.
        }
    }

    // TODO : indicate failed to find source code.
}

void HandleDefineDirective(Directive* directive, LexerContext* lexer, bool isFuncLike)
{
    std::string Identifier;
    if (isFuncLike)
    {
        Identifier = directive->AsDirectiveFuncDefine()->GetName();
    }
    else
    {
        // If its not a function like macro
        // the macro will be handled as DirectiveOp2. 
        // and that identifier of directive will be in Op1.
        Identifier = directive->AsDirectiveOp2()->GetOp1();
    }

    if (lexer->LookupDefineTable(Identifier) != nullptr)
    {
        // TODO : Emit warning. the Identifer already exists.
        return;
    }

    // Register define directive into table.
    lexer->DefDefineExpr(Identifier, directive);
}


} // namespace Language
} // namespace Goto