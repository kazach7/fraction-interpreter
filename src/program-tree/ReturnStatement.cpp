#include "../../include/program-tree/ReturnStatement.h"
#include "../../include/program-tree/Number.h"
#include "../../include/environment/Environment.h"
namespace kazachTKOM{

ReturnStatement::ReturnStatement(std::unique_ptr<ArithmeticExpression> e)
{
    if (e) arithm_expr = std::move(e);
    else arithm_expr = std::nullopt;
}

void ReturnStatement::execute(Environment& env){
    auto value = arithm_expr ? std::make_unique<Number>((*arithm_expr)->evaluate(env)) : nullptr;
    env.return_value(std::move(value));
}

}
