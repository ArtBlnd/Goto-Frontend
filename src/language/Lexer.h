#ifndef __GOTO_FRONTEND_LANGUAGE_LEXER__
#define __GOTO_FRONTEND_LANGUAGE_LEXER__

#include <functional>
#include <string>
#include <vector>

namespace Goto
{
namespace Basic
{
class Engine;
class FileViewer;
}

namespace Language
{
class Token;
class Macro;

class LexerContext
{
    std::vector<Token*> lcTokens;
    std::vector<Macro*> lxMacros;
};

class Lexer
{
    LexerContext* lxContext = nullptr;

    Basic::Engine*     lxParentEngine = nullptr;
    Basic::FileViewer* lxTargetFile   = nullptr;

    size_t lxPrevIndex  = 0;
    size_t lxPrevColumn = 0;
    size_t lxPrevLine   = 0;

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
    char lxGetPrevChar();
    char lxGetNextChar();

    std::string lxParseStringBeforeEnd(char endToken);
    std::string lxParseStringBeforeEnd(std::function<bool(char, bool)> endFunc, bool isClosed);
    std::string lxParseStringBeforeEnd(std::function<bool(char)> endFunc);
        
public:
    Lexer() = delete;
    Lexer(Basic::FileViewer* targetFile, LexerContext* context);

    bool StartLexSourceCode();
};

bool lxTokenlizeSourceCode(LexerContext* context, Basic::FileViewer* fileView);

} // namespace Language
} // namespace Goto

#endif