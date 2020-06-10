#ifndef H_KAZACHTKOM_RETURNSTMT
#define H_KAZACHTKOM_RETURNSTMT

#include "Statement.h"
#include <memory>
#include <optional>
namespace kazachTKOM{

class ArithmeticExpression;

class ReturnStatement : public Statement {
public:
    ReturnStatement(std::unique_ptr<ArithmeticExpression>);
    void execute(Environment&);
private:
    std::optional<std::unique_ptr<ArithmeticExpression>> arithm_expr;
};

}
#endif // H_KAZACHTKOM_RETURNSTMT
