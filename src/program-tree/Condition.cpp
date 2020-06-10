#include "../../include/program-tree/Condition.h"
#include "../../include/program-tree/LogicalExpression.h"
#include "../../include/program-tree/AndExpression.h"
#include "../../include/program-tree/EqualityExpression.h"
#include "../../include/program-tree/RelationalExpression.h"
#include "../../include/program-tree/Comparable.h"
#include "../../include/program-tree/ArithmeticExpression.h"
#include "../../include/program-tree/MultiplicativeExpression.h"
#include "../../include/program-tree/Multiplicable.h"
namespace kazachTKOM{

Condition::Condition(std::unique_ptr<LogicalExpression> e)
    : expression(std::move(e)) {}

bool Condition::evaluate(Environment& env){
    return expression->evaluate(env);
}

}
