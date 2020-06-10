#ifndef H_KAZACHTKOM_ASSIGNMENT
#define H_KAZACHTKOM_ASSIGNMENT

#include <string>
#include <memory>
#include "Statement.h"
#include "Identifier.h"
#include "../Token.h"
namespace kazachTKOM{

class Environment;
class ArithmeticExpression;

class Assignment : public Statement {
public:
    Assignment(std::unique_ptr<Identifier>, const std::string&,
               std::unique_ptr<ArithmeticExpression>);
    void execute(Environment&);
private:
    std::unique_ptr<Identifier> var_name;
    const std::string oper;
    std::unique_ptr<ArithmeticExpression> arithm_expr;
};

}
#endif // H_KAZACHTKOM_ASSIGNMENT
