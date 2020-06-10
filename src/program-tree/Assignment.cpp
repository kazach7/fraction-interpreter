#include "../../include/program-tree/Assignment.h"
#include "../../include/environment/Variable.h"
#include "../../include/program-tree/ArithmeticExpression.h"
#include "../../include/program-tree/MultiplicativeExpression.h"
#include "../../include/program-tree/Multiplicable.h"
#include "../../include/program-tree/FunctionCall.h"
#include "../../include/program-tree/FunCallArgument.h"
#include "../../include/environment/Environment.h"
#include "../../include/exceptions/RuntimeException.h"
#include <cassert>
namespace kazachTKOM{

Assignment::Assignment(std::unique_ptr<Identifier> n, const std::string& o,
                       std::unique_ptr<ArithmeticExpression> e)
    : var_name(std::move(n)), oper(o), arithm_expr(std::move(e)) {}


void Assignment::execute(Environment& env){
    Variable* var = env.get_variable(var_name->get_value());
    if (var == nullptr){
        // The assignment is at the same time a declaration of new local variable.
        if (oper != "="){
            // Apparently it's one of: +=,-=,*=,/=, which are not allowed in a variable declaration.
            throw RuntimeException("Variable undeclared.", var_name->get_line_no(), var_name->get_char_no());
        }
        // The following will never throw, as there is no such variable declared.
        env.add_variable(std::make_unique<Variable>(var_name->get_value(), arithm_expr->evaluate(env)));
    }
    else {
        if (oper == "=") var->set_value(arithm_expr->evaluate(env));
        else if (oper == "+=") var->set_value(var->get_value() + arithm_expr->evaluate(env));
        else if (oper == "-=") var->set_value(var->get_value() - arithm_expr->evaluate(env));
        else if (oper == "*=") var->set_value(var->get_value() * arithm_expr->evaluate(env));
        else if (oper == "/=") var->set_value(var->get_value() / arithm_expr->evaluate(env));
        else assert(((void)"Operator is none of: =,+=,-=,*=,/=", false));
    }
}

}
