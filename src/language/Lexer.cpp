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

std::string Lexer::lxParseStringBeforeEnd(std::function<bool(char, bool)> endFunc, bool isClosed)
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

std::string Lexer::lxParseStringBeforeEnd(std::function<bool(char)> endFunc)
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