#ifndef H_KAZACHTKOM_MULTIPLICABLE
#define H_KAZACHTKOM_MULTIPLICABLE

#include <memory>
#include "Number.h"
#include "FunctionCall.h"
#include "Identifier.h"
#include "ArithmeticExpression.h"
namespace kazachTKOM{

class Environment;
class ArithmeticExpression;
class FunctionCall;

class Multiplicable {
public:
    Multiplicable(const bool, const long, const unsigned int, const unsigned int);
    Multiplicable(const bool, std::unique_ptr<Identifier>, const unsigned int, const unsigned int);
    Multiplicable(const bool, std::unique_ptr<FunctionCall>, const unsigned int, const unsigned int);
    Multiplicable(const bool, std::unique_ptr<ArithmeticExpression>, const unsigned int, const unsigned int);

    Number evaluate(Environment&);
    const unsigned int get_line_no() const;
    const unsigned int get_char_no() const;
private:
    enum TYPE_STORED{
        ARITHM_EXPR, FUN_CALL, VAR_NAME, NUMBER
    };
    const enum TYPE_STORED type;
    const bool is_negative;
    std::unique_ptr<ArithmeticExpression> arithm_expr;
    std::unique_ptr<FunctionCall> fun_call;
    std::unique_ptr<Identifier> var_name;
    long number;
    const unsigned int line_no;
    const unsigned int char_no;
};

}
#endif // H_KAZACHTKOM_MULTIPLICABLE
