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
} // namespace Basic

namespace Language
{
class Token;
class Directive;

class LexerContext
{
    std::vector<Token*> lcTokens;

    std::vector<Directive*> lcPragmas;
    std::vector<Directive*> lcIfScope;

public:
    size_t GetTokenCount() const;
    Token* LookupToken(size_t index);

    void PushIfScope(Directive* directiveIf);
    void PopIfScope();

    void DefDefineExpr(std::string Key, Directive* directiveDefine);
    void UndefDefineExpr(std::string Key);
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

    bool lxSkipToken = false;

    void lxApplyChange();
    void lxUndoChange();

public:
    bool lxIsEOF();
    bool lxSkipSpace(bool applyChange = true);

    void lxConsumeChar();
    char lxConsumeAndGetChar();
    char lxGetCurrChar();
    char lxGetPrevChar();
    char lxGetNextChar();

    bool IsSkipTokenEnabled();
    void StartSkipToken();
    void StopSkipToken();

    std::string lxParseStringBeforeEnd(char endToken);
    std::string lxParseStringBeforeEnd(bool (*endFunc)(char, bool), bool isClosed);
    std::string lxParseStringBeforeEnd(bool (*endFunc)(char));
    std::string lxParseStringBeforeEnd(std::function<bool(char, bool)>& endFunc, bool isClosed);
    std::string lxParseStringBeforeEnd(std::function<bool(char)>& endFunc);

    Lexer() = delete;
    Lexer(Basic::FileViewer* targetFile, LexerContext* context);

    bool StartLexSourceCode();
};

bool lxTokenlizeSourceCode(LexerContext* context, Basic::FileViewer* fileView);

} // namespace Language
} // namespace Goto

#endif