#include "../../include/program-tree/Multiplicable.h"
#include "../../include/environment/Environment.h"
#include "../../include/exceptions/RuntimeException.h"
#include <cassert>
namespace kazachTKOM{

Multiplicable::Multiplicable(const bool neg, const long num, 
                             const unsigned int line, const unsigned int ch)
    : type(NUMBER), is_negative(neg), number(num), line_no(line), char_no(ch) {}

Multiplicable::Multiplicable(const bool neg, std::unique_ptr<Identifier> name,
                             const unsigned int line, const unsigned int ch)
    : type(VAR_NAME), is_negative(neg), var_name(std::move(name)), line_no(line), char_no(ch) {}

Multiplicable::Multiplicable(const bool neg, std::unique_ptr<FunctionCall> c,
                             const unsigned int line, const unsigned int ch)
    : type(FUN_CALL), is_negative(neg), fun_call(std::move(c)), line_no(line), char_no(ch) {}

Multiplicable::Multiplicable(const bool neg, std::unique_ptr<ArithmeticExpression> e,
                             const unsigned int line, const unsigned int ch)
    : type(ARITHM_EXPR), is_negative(neg), arithm_expr(std::move(e)), line_no(line), char_no(ch) {}

const unsigned int Multiplicable::get_line_no() const {
    return line_no;
}
const unsigned int Multiplicable::get_char_no() const {
    return char_no;
}
Number Multiplicable::evaluate(Environment& env){
    Number result;
    switch (type){
    case ARITHM_EXPR:
        result = arithm_expr->evaluate(env);
        break;
    case FUN_CALL:
        {
            auto returned_value = fun_call->execute(env);
            if (!returned_value){
                throw RuntimeException("Can't evaluate a void-returning function.",
                                       line_no, char_no);
            }
            result = *returned_value;
        }
        break;
    case VAR_NAME:
        {
            auto var = env.get_variable(var_name->get_value());
            if (!var){
                throw RuntimeException("Variable undeclared.", line_no, char_no);
            }
            result = var->get_value();
        }
        break;
    case NUMBER:
        result = Number(number);
        break;
    default:
        break;
    }
    if (is_negative) result = result * Number(-1,1);

    return result;
}

}
