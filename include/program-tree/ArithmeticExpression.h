#ifndef H_KAZACHTKOM_ARITHMEXPR
#define H_KAZACHTKOM_ARITHMEXPR

#include <memory>
#include <vector>
#include "../Token.h"
#include "MultiplicativeExpression.h"
namespace kazachTKOM{

class Environment;
class MultiplicativeExpression;
class Number;

class ArithmeticExpression {
public:
    ArithmeticExpression(std::vector<std::unique_ptr<MultiplicativeExpression>>,
                         std::vector<std::string>);
    Number evaluate(Environment&);

private:
    std::vector<std::unique_ptr<MultiplicativeExpression>> expressions;
    std::vector<std::string> operators;
};

}
#endif // H_KAZACHTKOM_ARITHMEXPR
