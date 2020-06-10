#include "../../include/program-tree/AndExpression.h"
#include "../../include/program-tree/EqualityExpression.h"
#include "../../include/program-tree/RelationalExpression.h"
#include "../../include/program-tree/LogicalExpression.h"
#include "../../include/program-tree/ArithmeticExpression.h"
#include "../../include/program-tree/MultiplicativeExpression.h"
#include "../../include/program-tree/Multiplicable.h"
#include "../../include/program-tree/Comparable.h"
namespace kazachTKOM{

AndExpression::AndExpression(std::vector<std::unique_ptr<EqualityExpression>> e)
    : expressions(std::move(e)) {}

double AndExpression::evaluate(Environment& env){
    auto it = expressions.begin();
    auto result = (*it)->evaluate(env);
    while (++it != expressions.end()){
        result = static_cast<double>(result && (*it)->evaluate(env));
    }
    return result;
}

}
