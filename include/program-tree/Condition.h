#ifndef H_KAZACHTKOM_CONDITION
#define H_KAZACHTKOM_CONDITION

#include <memory>
#include "LogicalExpression.h"
namespace kazachTKOM{

class Environment;
class LogicalExpression;

class Condition{
public:
    Condition(std::unique_ptr<LogicalExpression>);
    bool evaluate(Environment&);
private:
    std::unique_ptr<LogicalExpression> expression;
};

}
#endif // H_KAZACHTKOM_CONDITION
