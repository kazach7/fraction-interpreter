#include "../../include/program-tree/FunctionCall.h"
#include "../../include/program-tree/FunCallArgument.h"
#include "../../include/environment/Environment.h"
#include "../../include/exceptions/RuntimeException.h"
namespace kazachTKOM{

FunctionCall::FunctionCall(std::unique_ptr<Identifier> n,
                           std::vector<std::unique_ptr<FunCallArgument>> a)
    : fun_name(std::move(n)), args(std::move(a)) {}

std::optional<Number> FunctionCall::execute(Environment& env){
    Function* fun = env.get_function(fun_name->get_value(), args.size());
    if (fun == nullptr){
        throw RuntimeException("Attempt to call an undeclared function.",
                               fun_name->get_line_no(), fun_name->get_char_no());
    }

    std::vector<FunCallArgument*> v;
    for (auto &arg : args){
        v.push_back(arg.get());
    }
    return fun->call(v, env);
}

}
