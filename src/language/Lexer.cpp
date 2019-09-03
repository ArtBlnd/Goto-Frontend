#include <language/Lexer.h>
#include <language/LexerDirective.h>

#include <basic/Debug.h>
#include <basic/Indicator.h>
#include <basic/FileUtils.h>
#include <basic/Engine.h>

#include <language/TokenTable.h>

namespace Goto
{
namespace Language
{

// ============================================================
// LexerContext Implements Section
// ============================================================

size_t LexerContext::GetTokenCount() const
{
    return lcTokens.size();
}

Token* LexerContext::LookupToken(size_t index)
{
    return lcTokens[index];
}

void LexerContext::ApplyDirectiveIf(Directive* directive)
{
    switch (directive->GetType())
    {
        case DirectiveType::DT_ELSE:
        {
            noway_assert(directive->IsDirectiveNoOp(), "Unknown DirectiveType!");
            if (IsIfScopeEnabled.empty())
            {
                // Emit warning
            }

            if (IsIfScopeEnabled.back() == true)
            {
                IsIfScopeEnabled.back() = false;
            }
            else
            {
                IsIfScopeEnabled.back() = true;
            }
            break;
        }

        case DirectiveType::DT_ELSE_IF:
        {
            noway_assert(directive->IsDirectiveIf(), "Unknown DirectiveType!");
            if (IsIfScopeEnabled.empty())
            {
                // Emit warning
            }

            if (IsIfScopeEnabled.back() == true)
            {
                IsIfScopeEnabled.back() = false;
            }
            else
            {
                IsIfScopeEnabled.back() = directive->AsDirectiveIf()->IsExprTrue();
            }
            break;
        }

        case DirectiveType::DT_ENDIF:
        {
            noway_assert(directive->IsDirectiveNoOp(), "Unknown DirectiveType!");
            if (IsIfScopeEnabled.empty())
            {
                // Emit Error
            }

            IsIfScopeEnabled.pop_back();
            break;
        }

        case DirectiveType::DT_IF:
        {
            noway_assert(directive->IsDirectiveIf(), "Unknown DirectiveType!");
            IsIfScopeEnabled.push_back(directive->AsDirectiveIf()->IsExprTrue());

            break;
        }

        case DirectiveType::DT_IFDEF:
        {
            noway_assert(directive->IsDirectiveOp1(), "Unknown DirectiveType!");
            bool isExists = LookupDefineTable(directive->AsDirectiveOp1()->GetOp1()) != nullptr;
            IsIfScopeEnabled.push_back(isExists);

            break;
        }

        case DirectiveType::DT_IFNDEF:
        {
            noway_assert(directive->IsDirectiveOp1(), "Unknown DirectiveType!");
            bool isExists = LookupDefineTable(directive->AsDirectiveOp1()->GetOp1()) != nullptr;
            IsIfScopeEnabled.push_back(!isExists);

            break;
        }

        default:
            noway_assert(false, "Unknown DirectiveType!");
    }
}

// ============================================================
// Lexer Implements Section
// ============================================================

LexerContext* Lexer::GetLexerContext()
{
    return lxContext;
}

bool Lexer::lxIsEOF()
{
    noway_assert(lxCurrIndex > lxSrcFileLen, "Index cannot be larger than source file length!");
    return lxCurrIndex == lxTargetFile->GetFileSize();
}

bool Lexer::lxSkipSpace(bool applyChange)
{
    if (ttIsSpace(lxGetCurrChar()))
    {
        return false;
    }

    while (!lxIsEOF())
    {
        if (!ttIsSpace(lxConsumeAndGetChar()))
        {
            break;
        }
    }

    if (applyChange)
    {
        lxApplyChange();
    }

    return true;
}

bool Lexer::lxSkipSpace()
{
    return lxSkipSpace(false);
}

void Lexer::lxApplyChange()
{
    lxPrevIndex  = lxCurrIndex;
    lxPrevColumn = lxCurrColumn;
    lxPrevLine   = lxCurrLine;
}

void Lexer::lxUndoChange()
{
    lxCurrIndex  = lxPrevIndex;
    lxCurrColumn = lxPrevColumn;
    lxCurrLine   = lxPrevLine;
}

void Lexer::lxConsumeChar()
{
    noway_assert(!lxIsEOF(), "Lexer index is on EOF(End of file)!");

    if (ttIsNextLine(lxGetCurrChar()))
    {
        lxCurrColumn = 0;
        lxCurrLine++;
    }
    else
    {
        lxCurrColumn++;
    }

    lxCurrIndex++;
}

char Lexer::lxConsumeAndGetChar()
{
    noway_assert(!lxIsEOF(), "Lexer index is on EOF(End of file)!");

    char c = lxGetCurrChar();
    lxConsumeChar();

    return c;
}

char Lexer::lxGetCurrChar()
{
    return lxTargetFile->GetBuffer()[lxCurrIndex];
}

char Lexer::lxGetNextChar()
{
    noway_assert(!lxIsEOF(), "Lexer index is on EOF(End of file)!");

    return lxTargetFile->GetBuffer()[lxCurrIndex + 1];
}

char Lexer::lxGetPrevChar()
{
    noway_assert(lxCurrIndex != 0, "Cannot get prev char in buffer!");
    return lxTargetFile->GetBuffer()[lxCurrIndex + 1];
}

Lexer::Lexer(Basic::FileViewer* targetFile, LexerContext* context) : lxTargetFile(targetFile), lxContext(context)
{
    noway_assert(targetFile != nullptr, "Target file viewer cannot be nullptr!");
    noway_assert(context != nullptr, "Lexer context cannot be nullptr!");
}

std::string Lexer::lxParseStringBeforeEnd(char endToken)
{
    std::string token = "";

    while (lxIsEOF())
    {
        if (lxGetCurrChar() == endToken)
        {
            break;
        }

        token += lxConsumeAndGetChar();
    }

    return token;
}

std::string Lexer::lxParseStringBeforeEnd(bool (*endFunc)(char, bool), bool isClosed)
{
    std::string token = "";

    while (lxIsEOF())
    {
        if (endFunc(lxGetCurrChar(), isClosed))
        {
            break;
        }

        token += lxConsumeAndGetChar();
    }

    return token;
}

std::string Lexer::lxParseStringBeforeEnd(bool (*endFunc)(char))
{
    std::string token = "";

    while (lxIsEOF())
    {
        if (endFunc(lxGetCurrChar()))
        {
            break;
        }

        token += lxConsumeAndGetChar();
    }

    return token;
}

std::string Lexer::lxParseStringBeforeEnd(const std::function<bool(char, bool)>& endFunc, bool isClosed)
{
    std::string token = "";

    while (lxIsEOF())
    {
        if (endFunc(lxGetCurrChar(), isClosed))
        {
            break;
        }

        token += lxConsumeAndGetChar();
    }

    return token;
}

std::string Lexer::lxParseStringBeforeEnd(const std::function<bool(char)>& endFunc)
{
    std::string token = "";

    while (lxIsEOF())
    {
        if (endFunc(lxGetCurrChar()))
        {
            break;
        }

        token += lxConsumeAndGetChar();
    }

    return token;
}

/* StartLexSourceCode
 *
 * Description:
 *      Implmenetation of lexing codes.
 * Returns :
 *      Returning true if successed to lex source code
 */
bool Lexer::StartLexSourceCode()
{
    while (lxIsEOF())
    {
        if (ttIsSharp(lxGetCurrChar()))
        {
            // We should handle preprocessor directives in here
            // Handle it from LexerDriective
            Directive* newDirective = ParseDriectiveFrom(this);
            if (newDirective == nullptr)
            {
                lxApplyChange();
                continue;
            }

            noway_assert(newDirective->GetFunc() != DirectiveFunc::DF_UNKNOWN,
                         "Parsed directive function cannot be unknown!");
            noway_assert(newDirective->GetType() != DirectiveType::DT_UNKNOWN,
                         "Parsed directive type cannot be unknown!");

            switch (newDirective->GetType())
            {
                case DirectiveType::DT_INCLUDE:
                    // HandleIncludeDirective will modify context. which will tokenlize included file.
                    HandleIncludeDirective(newDirective, this->lxContext);
                    break;

                case DirectiveType::DT_DEFINE:
                    // Handling define will register a lexer level identifier on LexerContext.
                    // If the function type of directive is not a DF_FUNC_DEFINE its not a function like define.
                    HandleDefineDirective(newDirective, this->lxContext, newDirective->IsDirectiveOp1());
                    break;

                case DirectiveType::DT_ELSE:
                case DirectiveType::DT_ELSE_IF:
                case DirectiveType::DT_ENDIF:
                case DirectiveType::DT_IFDEF:
                case DirectiveType::DT_IFNDEF:
                    // Handling all kind of conditional directive
                    lxContext->ApplyDirectiveIf(newDirective);
                    break;

                case DirectiveType::DT_ERROR:
                    // TODO : internal error.
                    break;

                case DirectiveType::DT_LINE:
                    break;

                case DirectiveType::DT_PRAGMA:
                    break;

                case DirectiveType::DT_UNDEF:
                {
                    noway_assert(newDirective->IsDirectiveOp1(), "Undef directive should be DirectiveOp1");
                    lxContext->UndefDefineExpr(newDirective->AsDirectiveOp1()->GetOp1());
                    break;
                }

                case DirectiveType::DT_UNKNOWN:
                default:
                    noway_assert(false, "Unknown directive type!");
                    break;
            }

            // We do not undo change when parsing driective.
            lxApplyChange();
        }
    }
}

/* lxTokenlizeSourceCode
 *
 * Description:
 *      Record parsed tokens and macros in context with specific file viewer which contains target file buffer.
 *      this can also used with include macro.
 * Params :
 *      LexerContext* context : output of lexed informations.
 *      Basic::FileViewer* fileView : target file viewer.
 * Returns :
 *      Returning true if successed to lex source code
 */
bool lxTokenlizeSourceCode(LexerContext* context, Basic::FileViewer* fileView)
{
    noway_assert(fileView != nullptr, "Target file viewer cannot be nullptr!");
    noway_assert(context != nullptr, "Lexer context cannot be nullptr!");

    return Lexer(fileView, context).StartLexSourceCode();
}

} // namespace Language
} // namespace Goto