#include "../../include/program-tree/ArithmeticExpression.h"
#include "../../include/program-tree/MultiplicativeExpression.h"
#include "../../include/program-tree/Multiplicable.h"
#include "../../include/program-tree/FunctionCall.h"
#include "../../include/program-tree/FunCallArgument.h"
#include "../../include/program-tree/Number.h"
#include <cassert>
namespace kazachTKOM{

ArithmeticExpression::ArithmeticExpression(std::vector<std::unique_ptr<MultiplicativeExpression>> e,
                         std::vector<std::string> o)
    : expressions(std::move(e)), operators(std::move(o))
{
    assert(expressions.size() == operators.size() + 1);
}

Number ArithmeticExpression::evaluate(Environment& env){
    auto op_iter = operators.begin();
    auto expr_iter = expressions.begin();
    Number result = (*expr_iter)->evaluate(env);

    while (++expr_iter != expressions.end()){
        if (*op_iter == "+"){
            result = result + (*expr_iter)->evaluate(env);
        }
        else if (*op_iter == "-"){
            result = result - (*expr_iter)->evaluate(env);
        }
        else {
            assert (((void)"Operator is none of: +,-", false));
        }
        ++op_iter;
    }
    return result;
}

}
