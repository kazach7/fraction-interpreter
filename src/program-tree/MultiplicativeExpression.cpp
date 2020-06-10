#include "../../include/program-tree/MultiplicativeExpression.h"
#include "../../include/program-tree/Multiplicable.h"
#include "../../include/exceptions/RuntimeException.h"
#include <cassert>
namespace kazachTKOM{

MultiplicativeExpression::MultiplicativeExpression(std::vector<std::unique_ptr<Multiplicable>> e,
                                                   std::vector<std::string> o)
    : expressions(std::move(e)), operators(std::move(o))
{
    assert(expressions.size() == operators.size() + 1);
}
Number MultiplicativeExpression::evaluate(Environment& env){
    auto op_iter = operators.begin();
    auto expr_iter = expressions.begin();
    auto result = (*expr_iter)->evaluate(env);

    while (++expr_iter != expressions.end()){
        if (*op_iter == "*"){
            result = result * (*expr_iter)->evaluate(env);
        }
        else if (*op_iter == "/"){
            Number right_side = (*expr_iter)->evaluate(env);
            if (right_side == Number(0,1)){
                throw RuntimeException("Can't divide by 0!", 
                                       (*expr_iter)->get_line_no(), (*expr_iter)->get_char_no());
            }
            result = result / right_side;
        }
        else {
            assert (((void)"Operator is none of: *,/", false));
        }
        ++op_iter;
    }
    return result;
}

}
