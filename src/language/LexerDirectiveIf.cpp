#include <Language/LexerDirectiveIf.h>
#include <Language/Lexer.h>
#include <Language/Transform.h>

#include <Basic/Debug.h>

namespace Goto
{
namespace Language
{
IfExprIdentifier::IfExprIdentifier(std::string identifier) : Identifier(identifier) {}

uint64_t IfExprIdentifier::Evaluate(Lexer* lexer)
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

const std::string IfExprIdentifier::GetIdentifier() const
{
    return Identifier;
}

IfExprUnaryOp::IfExprUnaryOp(UnaryOpType type, IfExpr* expr) : uoType(type), uoExpr(expr) {}

uint64_t IfExprUnaryOp::Evaluate(Lexer* lexer)
{
    if (uoType == UnaryOpType::DEFINED_OP)
    {
        IfExprIdentifier* identifier = dynamic_cast<IfExprIdentifier*>(uoExpr);
        noway_assert(identifier != nullptr, "Operand of defiend operator should be identifier!");

        return lexer->GetLexerContext()->LookupDefineTable(identifier->GetIdentifier()) != nullptr;
    }

    switch (uoType)
    {
        case UnaryOpType::PLUS_OP:
            // + operator
            return +uoExpr->Evaluate(lexer);

        case UnaryOpType::MINUS_OP:
            // - operator
            return -uoExpr->Evaluate(lexer);

        case UnaryOpType::LOGICAL_NOT_OP:
            // ! operator
            return !uoExpr->Evaluate(lexer);

        case UnaryOpType::BITWISE_NOT_OP:
            // ~ operator.
            return ~uoExpr->Evaluate(lexer);

        default:
            break;
    }

    noway_assert(true, "Unknown UnaryOpType!");
}

uint64_t EvaluateIfExpr(Lexer* lexer)
{
    return 0;
}

} // namespace Language
} // namespace Goto
