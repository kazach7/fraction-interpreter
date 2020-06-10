#ifndef H_KAZACHTKOM_MULTIPEXPR
#define H_KAZACHTKOM_MULTIPEXPR

#include "../Token.h"
#include "Multiplicable.h"
namespace kazachTKOM{

class Environment;
class Multiplicable;

class MultiplicativeExpression {
public:
    MultiplicativeExpression(std::vector<std::unique_ptr<Multiplicable>>,
                             std::vector<std::string>);
    Number evaluate(Environment&);
private:
    std::vector<std::unique_ptr<Multiplicable>> expressions;
    std::vector<std::string> operators;
};

}
#endif // H_KAZACHTKOM_MULTIPEXPR
