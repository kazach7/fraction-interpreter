#ifndef H_KAZACHTKOM_ANDEXPR
#define H_KAZACHTKOM_ANDEXPR

#include <memory>
#include <vector>
#include "EqualityExpression.h"
namespace kazachTKOM{

class Environment;
class EqualityExpression;

class AndExpression {
public:
    AndExpression(std::vector<std::unique_ptr<EqualityExpression>>);
    double evaluate(Environment&);
private:
    std::vector<std::unique_ptr<EqualityExpression>> expressions;
};

}
#endif // H_KAZACHTKOM_ANDEXPR
