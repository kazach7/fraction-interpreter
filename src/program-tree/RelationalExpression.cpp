#include "../../include/program-tree/RelationalExpression.h"
#include "../../include/program-tree/Comparable.h"
#include <cassert>
namespace kazachTKOM{

RelationalExpression::RelationalExpression(std::vector<std::unique_ptr<Comparable>> e,
                                           std::vector<std::string> o)
    : expressions(std::move(e)), operators(std::move(o))
{
    assert(expressions.size() == operators.size() + 1);
}

double RelationalExpression::evaluate(Environment& env){
    auto op_iter = operators.begin();
    auto expr_iter = expressions.begin();
    auto result = (*expr_iter)->evaluate(env);

    while (++expr_iter != expressions.end()){
        if (*op_iter == "<"){
            result = static_cast<double>(result < (*expr_iter)->evaluate(env));
        }
        else if (*op_iter == ">"){
            result = static_cast<double>(result > (*expr_iter)->evaluate(env));
        }
        else if (*op_iter == "<="){
            result = static_cast<double>(result <= (*expr_iter)->evaluate(env));
        }
        else if (*op_iter == ">="){
            result = static_cast<double>(result >= (*expr_iter)->evaluate(env));
        }
        else {
            assert (((void)"Operator is none of: <,>,<=,>=", false));
        }
        ++op_iter;
    }
    return result;
}

}
