#ifndef H_KAZACHTKOM_ENVIRONMENT
#define H_KAZACHTKOM_ENVIRONMENT

#include <memory>
#include <vector>
#include "Scope.h"
#include "FunctionScope.h"
#include "Function.h"
namespace kazachTKOM{

class Variable;
class Number;
class FunctionScope;
class Function;

class Environment {
public:
    Environment();

    void make_function_scope(); // A function has been called - push the new scope for it
                                // to the function scopes stack.
    void make_local_scope(); // Push a new scope to the local scopes stack of the currently 
                             // executed function.
    void destroy_function_scope(); // Function execution has ended - pop its scope
                                   // from the function scopes stack.
    void destroy_local_scope(); // Pop the scope from the local scopes stack of the currently executed
                                // function.

    void add_variable(std::unique_ptr<Variable>);
    Variable* get_variable(const std::string&);

    void add_function(std::unique_ptr<Function>);
    Function* get_function(const std::string&, int);

    void return_value(std::unique_ptr<Number>);
    std::unique_ptr<Number> get_returned_value();
    bool has_returned() const; 
private:
    Scope global_scope; // Variables seen in every scope.
    std::vector<FunctionScope> function_scopes; // Function scopes stack - each fun scope contains
                                                // function call arguments and a local scopes stack.
    std::vector<std::unique_ptr<Function>> functions; // Defined functions.
    std::unique_ptr<Number> returned_value; // Value returned in the last executed return statement.
    bool has_returned_; // Indicates if a return statement has been executed in the
                        // currently executed function (used to find out if execution
                        // of the function should finish).
};

}
#endif // H_KAZACHTKOM_ENVIRONMENT
