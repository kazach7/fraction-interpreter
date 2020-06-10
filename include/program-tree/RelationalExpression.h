#ifndef H_KAZACHTKOM_RELATIONALEXPR
#define H_KAZACHTKOM_RELATIONALEXPR

#include "../Token.h"
#include "Comparable.h"
namespace kazachTKOM{

class Comparable;
class Environment;

class RelationalExpression {
public:
    RelationalExpression(std::vector<std::unique_ptr<Comparable>>,
                         std::vector<std::string>);
    double evaluate(Environment&);
private:
    std::vector<std::unique_ptr<Comparable>> expressions;
    std::vector<std::string> operators;
};

}
#endif // H_KAZACHTKOM_RELATIONALEXPR
