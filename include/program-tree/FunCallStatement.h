#ifndef H_KAZACHTKOM_FUNCALLSTMT
#define H_KAZACHTKOM_FUNCALLSTMT

#include <memory>
#include "Statement.h"
namespace kazachTKOM{

class Environment;
class FunctionCall;

class FunCallStatement : public Statement {
public:
    FunCallStatement(std::unique_ptr<FunctionCall>);
    void execute(Environment&);
private:
    std::unique_ptr<FunctionCall> fun_call;
};

}
#endif // H_KAZACHTKOM_FUNCALLSTMT
