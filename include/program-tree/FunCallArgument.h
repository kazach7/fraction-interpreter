#ifndef H_KAZACHTKOM_FUNCALLPARAM
#define H_KAZACHTKOM_FUNCALLPARAM

#include <memory>
#include "Number.h"
#include "ArithmeticExpression.h"
namespace kazachTKOM{

class Environment;
class ArithmeticExpression;

class FunCallArgument {
public:
    FunCallArgument(std::unique_ptr<ArithmeticExpression>);
    Number evaluate(Environment&);
private:
    std::unique_ptr<ArithmeticExpression> expression;
};

}
#endif // H_KAZACHTKOM_FUNCALLPARAM
