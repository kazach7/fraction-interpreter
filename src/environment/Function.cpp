#include "../../include/environment/Function.h"
namespace kazachTKOM{

Function::Function(const std::string& n, const std::vector<std::string>& p,
                   StatementBlock* b)
    : fun_name(n), params(p), stmt_block(b) {}

std::optional<Number> Function::call(std::vector<FunCallArgument*>& call_params, Environment& env){
    std::vector<std::unique_ptr<Variable>> v;
    auto it = call_params.begin();
    for (auto &p : this->params){
        v.push_back(std::make_unique<Variable>(p, (*it++)->evaluate(env)));
    }

    env.make_function_scope();
    for (auto &variable : v){
        env.add_variable(std::move(variable));
    }
    stmt_block->execute(env);
    auto returned_value = env.get_returned_value();
    env.destroy_function_scope();

    if (returned_value){
        return *returned_value;
    }
    return std::nullopt;
}
const std::string Function::get_name() const{
    return fun_name;
}
const int Function::get_param_count() const{
    return params.size();
}

}
