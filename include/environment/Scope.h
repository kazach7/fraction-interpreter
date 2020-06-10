#ifndef H_KAZACHTKOM_SCOPE
#define H_KAZACHTKOM_SCOPE

#include <memory>
#include <map>
#include "Variable.h"
namespace kazachTKOM{

class Number;

class Scope{
public:
    virtual void add_variable (std::unique_ptr<Variable>);
    virtual Variable* get_variable(const std::string&);
protected:
    std::unique_ptr<Variable> dummy; // <-- This prevents C2280 error related to the 'variables' std::map in VS2019 (for some reason).
    std::map<std::string, std::unique_ptr<Variable>> variables;
};

}
#endif // H_KAZACHTKOM_SCOPE
