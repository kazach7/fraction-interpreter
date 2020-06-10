#include "../../include/program-tree/FunCallArgument.h"
#include "../../include/program-tree/ArithmeticExpression.h"
namespace kazachTKOM{

FunCallArgument::FunCallArgument(std::unique_ptr<ArithmeticExpression> e)
    : expression(std::move(e)) {}

Number FunCallArgument::evaluate(Environment& env) {
    return expression->evaluate(env);
}

}
