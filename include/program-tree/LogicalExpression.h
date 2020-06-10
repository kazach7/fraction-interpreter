#ifndef H_KAZACHTKOM_LOGICALEXPR
#define H_KAZACHTKOM_LOGICALEXPR

#include <vector>
#include <memory>
#include "AndExpression.h"
namespace kazachTKOM{

class Environment;
class AndExpression;

class LogicalExpression {
public:
    LogicalExpression(std::vector<std::unique_ptr<AndExpression>>);
    double evaluate(Environment&);
private:
    std::vector<std::unique_ptr<AndExpression>> expressions;
};

}
#endif // H_KAZACHTKOM_LOGICALEXPR
