#include <Language/LexerDirectiveIf.h>
#include <Language/Lexer.h>
#include <Language/Transform.h>

#include <Basic/Debug.h>

namespace Goto
{
namespace Language
{
IfExprIdentifier::IfExprIdentifier(std::string identifier) : Identifier(identifier) {}

int64_t IfExprIdentifier::Evaluate(Lexer* lexer)
{
    LexerContext* lexerContext = lexer->GetLexerContext();

    if (Directive* defineExpr = lexerContext->LookupDefineTable(Identifier))
    {
        if (defineExpr->IsDirectiveOp2())
        {
            DirectiveOp2* defineOp2Expr = defineExpr->AsDirectiveOp2();
            return tfStr2IntegerTransform(defineOp2Expr->GetOp2());
        }
    }

    // Evaluate as zero if constant cannot be found.
    return 0;
}

const std::string IfExprIdentifier::GetIdentifier() const
{
    return Identifier;
}

IfExprUnaryOp::IfExprUnaryOp(UnaryOpTypes type, IfExpr* expr) : uoType(type), uoExpr(expr) {}

int64_t IfExprUnaryOp::Evaluate(Lexer* lexer)
{
    if (uoType == UnaryOpTypes::DEFINED_OP)
    {
        IfExprIdentifier* identifier = dynamic_cast<IfExprIdentifier*>(uoExpr);
        noway_assert(identifier != nullptr, "Operand of defiend operator should be identifier!");

        return lexer->GetLexerContext()->LookupDefineTable(identifier->GetIdentifier()) != nullptr;
    }

    switch (uoType)
    {
        case UnaryOpTypes::PLUS_OP:
            // + operator
            return +uoExpr->Evaluate(lexer);

        case UnaryOpTypes::MINUS_OP:
            // - operator
            return -uoExpr->Evaluate(lexer);

        case UnaryOpTypes::LOGICAL_NOT_OP:
            // ! operator
            return !uoExpr->Evaluate(lexer);

        case UnaryOpTypes::BITWISE_NOT_OP:
            // ~ operator.
            return ~uoExpr->Evaluate(lexer);

        default:
            break;
    }

    noway_assert(true, "Unknown UnaryOpType!");
}

IfExprBinaryOp::IfExprBinaryOp(BinaryOpTypes type, IfExpr* op1, IfExpr* op2) : boType(type), boExprL(op1), boExprR(op2)
{
}

int64_t IfExprBinaryOp::Evaluate(Lexer* lexer)
{
    switch (boType)
    {
        case BinaryOpTypes::PLUS_OP:
            return boExprL->Evaluate(lexer) + boExprR->Evaluate(lexer);

        case BinaryOpTypes::MINUS_OP:
            return boExprL->Evaluate(lexer) - boExprR->Evaluate(lexer);

        case BinaryOpTypes::MULTIPLY_OP:
            return boExprL->Evaluate(lexer) * boExprR->Evaluate(lexer);

        case BinaryOpTypes::DIVIDE_OP:
            return boExprL->Evaluate(lexer) / boExprR->Evaluate(lexer);

        case BinaryOpTypes::BITWISE_AND:
            return boExprL->Evaluate(lexer) & boExprR->Evaluate(lexer);

        case BinaryOpTypes::BITWISE_OR:
            return boExprL->Evaluate(lexer) | boExprR->Evaluate(lexer);

        case BinaryOpTypes::LOGICAL_AND_OP:
            return boExprL->Evaluate(lexer) && boExprR->Evaluate(lexer);

        case BinaryOpTypes::LOGICAL_OR_OP:
            return boExprL->Evaluate(lexer) || boExprR->Evaluate(lexer);

        case BinaryOpTypes::COMPARE_EQ:
            return boExprL->Evaluate(lexer) == boExprR->Evaluate(lexer);

        case BinaryOpTypes::COMPARE_NE:
            return boExprL->Evaluate(lexer) != boExprR->Evaluate(lexer);

        case BinaryOpTypes::COMPARE_LT:
            return boExprL->Evaluate(lexer) < boExprR->Evaluate(lexer);

        case BinaryOpTypes::COMPARE_LE:
            return boExprL->Evaluate(lexer) <= boExprR->Evaluate(lexer);

        case BinaryOpTypes::COMPARE_GT:
            return boExprL->Evaluate(lexer) > boExprR->Evaluate(lexer);

        case BinaryOpTypes::COMPARE_GE:
            return boExprL->Evaluate(lexer) >= boExprR->Evaluate(lexer);

        case BinaryOpTypes::XOR_OP:
            return boExprL->Evaluate(lexer) ^ boExprR->Evaluate(lexer);

        case BinaryOpTypes::LSHIFT_OP:
            return boExprL->Evaluate(lexer) << boExprR->Evaluate(lexer);

        case BinaryOpTypes::RSHIFT_OP:
            return boExprL->Evaluate(lexer) >> boExprR->Evaluate(lexer);

        default:
            break;
    }

    noway_assert(true, "Unknown BinaryOpType!");
}

IfExprConstant::IfExprConstant(int64_t constant) : Constant(constant) {}

int64_t IfExprConstant::Evaluate(Lexer* lexer) 
{
    return Constant;
}

int64_t EvaluateIfExpr(Lexer* lexer, std::string Expr)
{
    return 0;
}

} // namespace Language
} // namespace Goto
