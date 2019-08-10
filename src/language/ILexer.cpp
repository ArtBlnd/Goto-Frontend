#include <language/ILexer.h>

#include <basic/Debug.h>
#include <language/TokenTable.h>

namespace Goto
{
namespace Language
{

bool ILexer::lxIsEOF()
{
    noway_assert(lxCurrIndex > lxSrcFileLen, "Index cannot be larger than source file length!");
    return lxCurrIndex == lxSrcFileLen;
}

bool ILexer::lxSkipSpace(bool applyChange)
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

void ILexer::lxApplyChange()
{
    lxPrivIndex  = lxCurrIndex;
    lxPrivColumn = lxCurrColumn;
    lxPrivLine   = lxCurrLine;
}

void ILexer::lxUndoChange()
{
    lxCurrIndex  = lxPrivIndex;
    lxCurrColumn = lxPrivColumn;
    lxCurrLine   = lxPrivLine;
}

void ILexer::lxConsumeChar()
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

char ILexer::lxConsumeAndGetChar()
{
    char c = lxGetCurrChar();
    lxConsumeChar();

    return c;
}

char ILexer::lxGetCurrChar()
{
    return lxSrcFileBuf[lxCurrIndex];
}

char ILexer::lxGetNextChar()
{
    return lxSrcFileBuf[lxCurrIndex + 1];
}

char ILexer::lxGetPrivChar() 
{
    noway_assert(lxCurrIndex != 0, "Cannot get priv char in buffer!");
    return lxSrcFileBuf[lxCurrIndex + 1];
}

ILexer::ILexer(const char* srcFileBuf, size_t srcFileLen) : lxSrcFileBuf(srcFileBuf), lxSrcFileLen(srcFileLen)
{
    noway_assert(srcFileBuf != nullptr, "Source file buffer cannot be nullptr!");
    noway_assert(srcFileLen != 0, "Source file legnth cannot be zero!");
}

} // namespace Language
} // namespace Goto