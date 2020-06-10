#include "../../include/program-tree/FunCallStatement.h"
#include "../../include/program-tree/FunctionCall.h"
namespace kazachTKOM{

FunCallStatement::FunCallStatement(std::unique_ptr<FunctionCall> c)
    : fun_call(std::move(c)) {}

void FunCallStatement::execute(Environment& env){
    fun_call->execute(env);
}

}
