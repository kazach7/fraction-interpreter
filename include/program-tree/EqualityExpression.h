#ifndef H_KAZACHTKOM_EQUALITYEXPR
#define H_KAZACHTKOM_EQUALITYEXPR

#include <vector>
#include <memory>
#include "../Token.h"
#include "RelationalExpression.h"
namespace kazachTKOM{

class Environment;
class RelationalExpression;

class EqualityExpression {
public:
    EqualityExpression(std::vector<std::unique_ptr<RelationalExpression>>,
                       std::vector<std::string>);
    double evaluate(Environment&);
private:
    std::vector<std::unique_ptr<RelationalExpression>> expressions;
    std::vector<std::string> operators;
};

}
#endif // H_KAZACHTKOM_EQUALITYEXPR
