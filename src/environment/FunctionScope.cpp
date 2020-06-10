#include "../../include/environment/FunctionScope.h"
#include "../../include/environment/Variable.h"
#include <string>
namespace kazachTKOM{

void FunctionScope::push_local_scope(){
    local_scopes.push_back(Scope());
}
void FunctionScope::pop_local_scope(){
    local_scopes.pop_back();
}

void FunctionScope::add_variable(std::unique_ptr<Variable> var){
    if (local_scopes.empty()){
        this->variables[var->get_name()] = std::move(var);
    }
    else {
       local_scopes.back().add_variable(std::move(var));
    }
}
Variable* FunctionScope::get_variable(const std::string& var_name){
    // Iterate the local scopes stack from top to bottom.
    for (auto it = local_scopes.rbegin(); it != local_scopes.rend(); ++it){
        if (auto result = (*it).get_variable(var_name)){
            return result;
        }
    }
    // No such variable in the local scopes, so try to find it amongst the fun call arguments.
    if (auto it = variables.find(var_name); it != variables.end()){
        return it->second.get();
    }
    return nullptr;
}

}
