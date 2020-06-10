#include "../../include/program-tree/Comparable.h"
#include "../../include/program-tree/LogicalExpression.h"
#include "../../include/program-tree/AndExpression.h"
#include "../../include/program-tree/EqualityExpression.h"
#include "../../include/program-tree/RelationalExpression.h"
#include "../../include/program-tree/ArithmeticExpression.h"
#include "../../include/program-tree/MultiplicativeExpression.h"
#include "../../include/program-tree/Multiplicable.h"
#include "../../include/program-tree/Number.h"
namespace kazachTKOM{

Comparable::Comparable(const bool n, std::unique_ptr<LogicalExpression> e)
    : type(LOGICAL_EXPR), is_negated(n), logical_expr(std::move(e)) {}

Comparable::Comparable(std::unique_ptr<ArithmeticExpression> e)
    : type(ARITHM_EXPR), is_negated(false), arithm_expr(std::move(e)) {}

double Comparable::evaluate(Environment& env){
    if (type == LOGICAL_EXPR){
        auto result = logical_expr->evaluate(env);
        if (is_negated){
            if (result == 0) result = 1;
            else result = 0;
        }
        return result;
    }
    else { // type == ARITHM_EXPR
        Number numb = arithm_expr->evaluate(env);
        return static_cast<double>(numb.get_numerator()) / static_cast<double>(numb.get_denominator());
    }
}

}
