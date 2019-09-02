#ifndef __GOTO_FRONTEND_LANGUAGE_LEXER__
#define __GOTO_FRONTEND_LANGUAGE_LEXER__

#include <functional>
#include <string>
#include <vector>

#include <Language/LexerDirective.h>

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
    

    std::vector<bool> IsIfScopeEnabled;

public:
    size_t GetTokenCount() const;
    Token* LookupToken(size_t index);

    void ApplyDirectiveIf(Directive* directiveIf);
    bool IsOnDisabledIfScope();

    void DefDefineExpr(std::string Key, Directive* directiveDefine);
    void UndefDefineExpr(std::string Key);
    Directive* LookupDefineTable(std::string Key);

    Directive* AllocDirectiveNoOp(DirectiveType type);
    Directive* AllocDirectiveOp1(DirectiveType type, std::string Op1);
    Directive* AllocDirectiveOp2(DirectiveType type, std::string Op1, std::string Op2);
    Directive* AllocDirectiveFuncDefine(std::string DefineIdent, std::vector<std::string> ParamIdent, std::string Expr);;
    Directive* AllocDirectivePragma();
    Directive* AllocDirectiveIf(bool isExprTrue);
    Directive* AllocDirectiveInclude(std::string includePath, bool isLocal);
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

    bool lxSkipSpace(bool applyChange);

public:
    LexerContext* GetLexerContext();

    bool lxIsEOF();
    bool lxSkipSpace();

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
    std::string lxParseStringBeforeEnd(const std::function<bool(char, bool)>& endFunc, bool isClosed);
    std::string lxParseStringBeforeEnd(const std::function<bool(char)>& endFunc);

    Lexer() = delete;
    Lexer(Basic::FileViewer* targetFile, LexerContext* context);

    bool StartLexSourceCode();
};

bool lxTokenlizeSourceCode(LexerContext* context, Basic::FileViewer* fileView);

} // namespace Language
} // namespace Goto

#endif