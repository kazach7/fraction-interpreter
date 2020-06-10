#include "../../include/program-tree/StdoutPrint.h"
#include "../../include/modules/StdIOManager.h"
namespace kazachTKOM{

bool StdoutPrint::display_integral_part = false;

StdoutPrint::StdoutPrint(const std::string& s)
    : type(STRING), str(s) {}

StdoutPrint::StdoutPrint(std::unique_ptr<ArithmeticExpression> e)
    : type(ARITHM_EXPR), expr(std::move(e)) {}

void StdoutPrint::execute(Environment& env){
    StdIOManager iomanager;
    if (type == STRING){
        iomanager.print_on_stdout(str);
    }
    else { // type == ARITHM_EXPR
        Number numb = expr->evaluate(env);
        auto numer = numb.get_numerator();
        auto denom = numb.get_denominator();

        if (numer == 0 || denom == 1){
            iomanager.print_on_stdout(std::to_string(numer));
        }
        else {
            std::string output;
            if (display_integral_part) {
                long integral_part = numer / static_cast<long>(denom);
                if (integral_part != 0) {
                    numer -= integral_part * denom;
                    output += std::to_string(integral_part);
                    if (numer > 0) output += "+";
                }
            }
            output += std::to_string(numer) + "/" + std::to_string(denom);
            iomanager.print_on_stdout(output);
        }
    }
}

}
