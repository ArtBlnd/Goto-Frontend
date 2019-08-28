#include <Language/LexerDirectiveIf.h>
#include <Language/Lexer.h>
#include <Language/Transform.h>

Goto::Language::IfExprIdentifier::IfExprIdentifier(std::string identifier) : Identifier(identifier) {}

uint64_t Goto::Language::IfExprIdentifier::Evaluate(Lexer* lexer)
{
    LexerContext* lexerContext = lexer->GetLexerContext();

    if (Directive* defineExpr = lexerContext->LookupDefineTable(Identifier))
    {
        if (defineExpr->IsDirectiveOp2())
        {
            DirectiveOp2* defineOp2Expr = defineExpr->AsDirectiveOp2();
            return tfStr2IntegerTransform(defineOp2Expr->GetOp2());
        }
        else
        {
            // Evaluate as zero if its a function like macro.
            return 0;
        }
    }

    // Evaluate as zero if constant cannot be found.
    return 0;
}

uint64_t Goto::Language::EvaluateIfExpr(Lexer* lexer)
{
    return 0;
}