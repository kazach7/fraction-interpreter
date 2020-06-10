#ifndef H_KAZACHTKOM_COMPARABLE
#define H_KAZACHTKOM_COMPARABLE

#include <memory>
#include "LogicalExpression.h"
#include "ArithmeticExpression.h"
namespace kazachTKOM{

class Environment;
class LogicalExpression;
class ArithmeticExpression;

class Comparable {
public:
    Comparable(const bool, std::unique_ptr<LogicalExpression>);
    Comparable(std::unique_ptr<ArithmeticExpression>);
    double evaluate(Environment&);
private:
    enum TYPE_STORED{
        LOGICAL_EXPR, ARITHM_EXPR
    };
    const enum TYPE_STORED type;
    const bool is_negated;
    std::unique_ptr<LogicalExpression> logical_expr;
    std::unique_ptr<ArithmeticExpression> arithm_expr;
};

}
#endif // H_KAZACHTKOM_COMPARABLE
