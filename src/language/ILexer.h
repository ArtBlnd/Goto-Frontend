#ifndef __GOTO_FRONTEND_LANGUAGE_ILEXER__
#define __GOTO_FRONTEND_LANGUAGE_ILEXER__

namespace Goto
{
namespace Language
{

class ILexer
{
    const char* lxSrcFileBuf = nullptr;
    size_t      lxSrcFileLen = 0;

    size_t lxPrivIndex  = 0;
    size_t lxPrivColumn = 0;
    size_t lxPrivLine   = 0;

    size_t lxCurrIndex  = 0;
    size_t lxCurrColumn = 0;
    size_t lxCurrLine   = 0;

protected:
    bool lxIsEOF();
    bool lxSkipSpace(bool applyChange = true);

    void lxApplyChange();
    void lxUndoChange();

    void lxConsumeChar();
    char lxConsumeAndGetChar();
    char lxGetCurrChar();
    char lxGetPrivChar();
    char lxGetNextChar();

    ILexer() = delete;
    ILexer(const char* srcFileBuf, size_t srcFileLen);
};

} // namespace Language
} // namespace Goto

#endif