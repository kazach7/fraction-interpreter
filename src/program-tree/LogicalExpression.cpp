#include "../../include/program-tree/LogicalExpression.h"
#include "../../include/program-tree/AndExpression.h"
namespace kazachTKOM{

LogicalExpression::LogicalExpression(std::vector<std::unique_ptr<AndExpression>> e)
    : expressions(std::move(e)) {}

double LogicalExpression::evaluate(Environment& env){
    auto it = expressions.begin();
    auto result = (*it)->evaluate(env);
    while (++it != expressions.end()){
        result = static_cast<double>(result || (*it)->evaluate(env));
    }
    return result;
}

}
