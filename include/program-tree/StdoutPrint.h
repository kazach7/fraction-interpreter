#ifndef H_KAZACHTKOM_STDOUTPRINT
#define H_KAZACHTKOM_STDOUTPRINT

#include "Statement.h"
#include "ArithmeticExpression.h"
#include <memory>
namespace kazachTKOM{

class ArithmeticExpression;

class StdoutPrint : public Statement {
public:
    StdoutPrint(const std::string&);
    StdoutPrint(std::unique_ptr<ArithmeticExpression>);
    void execute(Environment&);

    static bool display_integral_part;
private:
    enum TYPE_STORED {
        STRING, ARITHM_EXPR
    };
    const enum TYPE_STORED type;
    std::string str;
    std::unique_ptr<ArithmeticExpression> expr;
};

}
#endif // K_KAZACHTKOM_STDOUTPRINT
