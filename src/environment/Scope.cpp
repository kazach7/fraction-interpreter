#include "../../include/environment/Scope.h"
#include "../../include/exceptions/EnvironmentException.h"
#include <string>
namespace kazachTKOM{

void Scope::add_variable (std::unique_ptr<Variable> var){
    if (this->get_variable(var->get_name())){
        throw EnvironmentException("Variable redeclaration in the same scope is not allowed.");
    }
    variables[var->get_name()] = std::move(var);
}
Variable* Scope::get_variable(const std::string& var_name){
    if (auto it = variables.find(var_name); it != variables.end()){
        return it->second.get();
    }
    return nullptr;
}

}
