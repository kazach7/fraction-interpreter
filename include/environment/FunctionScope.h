#ifndef H_KAZACHTKOM_FUNCTIONSCOPE
#define H_KAZACHTKOM_FUNCTIONSCOPE

#include <vector>
#include "Scope.h"
namespace kazachTKOM{


class FunctionScope : public Scope {
public:
    void push_local_scope();
    void pop_local_scope();

    virtual void add_variable(std::unique_ptr<Variable>);
    virtual Variable* get_variable(const std::string&);
private:
    std::vector<Scope> local_scopes;
};

}
#endif // H_KAZACHTKOM_FUNCTIONSCOPE
