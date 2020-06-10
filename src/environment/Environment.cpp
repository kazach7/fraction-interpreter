#include "../../include/environment/Environment.h"
#include "../../include/environment/FunctionScope.h"
#include "../../include/environment/Variable.h"
#include "../../include/program-tree/Number.h"
#include "../../include/program-tree/StatementBlock.h"
#include "../../include/exceptions/EnvironmentException.h"
#include <cassert>
namespace kazachTKOM{

Environment::Environment(){
    has_returned_ = false;
}
void Environment::make_function_scope(){
    function_scopes.push_back(FunctionScope());
    has_returned_ = false;
    returned_value.reset(); // Should already be null, but just in case.
}
void Environment::make_local_scope(){
    assert (!function_scopes.empty());

    function_scopes.back().push_local_scope();
}
void Environment::destroy_function_scope(){
    assert (!function_scopes.empty());

    function_scopes.pop_back();
    has_returned_ = false;
    returned_value.reset();
}
void Environment::destroy_local_scope(){
    assert (!function_scopes.empty());

    function_scopes.back().pop_local_scope();
}

void Environment::add_variable(std::unique_ptr<Variable> var){
    Scope& scope = function_scopes.empty() ? global_scope : function_scopes.back();
    scope.add_variable(std::move(var));
}
Variable* Environment::get_variable(const std::string& var_name){
    Variable* result;
    if (!function_scopes.empty() && (result = function_scopes.back().get_variable(var_name))){
        return result;
    }
    return global_scope.get_variable(var_name);
}

void Environment::add_function(std::unique_ptr<Function> fun){
    if (this->get_function(fun->get_name(), fun->get_param_count())){
        throw EnvironmentException("Function with that signature is already defined.");
    }
    functions.push_back(std::move(fun));
}
Function* Environment::get_function(const std::string& fun_name, int param_count){
    for (auto &f : functions){
        if (f->get_name() == fun_name && f->get_param_count() == param_count){
            return f.get();
        }
    }
    return nullptr;
}

void Environment::return_value(std::unique_ptr<Number> value){
    returned_value = std::move(value);
    has_returned_ = true;
}
bool Environment::has_returned() const {
    return has_returned_;
}
std::unique_ptr<Number> Environment::get_returned_value(){
    return std::move(returned_value);
}

}
