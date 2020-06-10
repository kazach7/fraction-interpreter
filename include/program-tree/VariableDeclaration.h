#ifndef H_KAZACHTKOM_VARIABLEDECL
#define H_KAZACHTKOM_VARIABLEDECL

#include "ArithmeticExpression.h"
#include "Identifier.h"
#include "Statement.h"
#include <optional>
namespace kazachTKOM{

class Environment;
class ArithmeticExpression;

class VariableDeclaration : public Statement {
public:
    VariableDeclaration(std::unique_ptr<Identifier>,
                        std::unique_ptr<ArithmeticExpression>);
    void execute(Environment&);
private:
    std::unique_ptr<Identifier> var_name;
    std::optional<std::unique_ptr<ArithmeticExpression>> right_side_expr;
};

}
#endif // H_KAZACHTKOM_VARIABLEDECL
