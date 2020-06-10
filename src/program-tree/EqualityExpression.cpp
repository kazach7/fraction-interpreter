#include "../../include/program-tree/EqualityExpression.h"
#include "../../include/program-tree/RelationalExpression.h"
#include <cassert>
namespace kazachTKOM{

EqualityExpression::EqualityExpression(std::vector<std::unique_ptr<RelationalExpression>> e,
                                       std::vector<std::string> o)
    : expressions(std::move(e)), operators(std::move(o))
{
    assert(expressions.size() == operators.size() + 1);
}

double EqualityExpression::evaluate(Environment& env){
    auto op_iter = operators.begin();
    auto expr_iter = expressions.begin();
    auto result = (*expr_iter)->evaluate(env);

    while (++expr_iter != expressions.end()){
        if (*op_iter == "=="){
            result = static_cast<double>(result == (*expr_iter)->evaluate(env));
        }
        else if (*op_iter == "!="){
            result = static_cast<double>(result != (*expr_iter)->evaluate(env));
        }
        else {
            assert (((void)"Operator is none of: ==,!=", false));
        }
        ++op_iter;
    }
    return result;
}

}
