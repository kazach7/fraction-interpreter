#include "../../include/program-tree/VariableDeclaration.h"
#include "../../include/environment/Environment.h"
#include "../../include/exceptions/EnvironmentException.h"
#include "../../include/exceptions/RuntimeException.h"
namespace kazachTKOM{

VariableDeclaration::VariableDeclaration(std::unique_ptr<Identifier> n, std::unique_ptr<ArithmeticExpression> e)
    : var_name(std::move(n))
{
    if (e) right_side_expr = std::move(e);
    else right_side_expr = std::nullopt;
}

void VariableDeclaration::execute(Environment& env){
    auto value = right_side_expr ? (*right_side_expr)->evaluate(env) : Number(0, 1);
    try {
        env.add_variable(std::make_unique<Variable>(var_name->get_value(), value));
    }
    catch (EnvironmentException& e){
        throw RuntimeException(e.what(), var_name->get_line_no(), var_name->get_char_no());
    }
}

}
