#include "../../include/program-tree/IfElse.h"
namespace kazachTKOM{

IfElse::IfElse(std::unique_ptr<Condition> c, std::unique_ptr<StatementBlock> t,
           std::unique_ptr<StatementBlock> f)
    : cond(std::move(c)), true_block(std::move(t)), false_block(std::move(f)) {}

void IfElse::execute(Environment& env){
    if (cond->evaluate(env)){
        true_block->execute(env);
    }
    else {
        if (false_block != nullptr){
            false_block->execute(env);
        }
    }
}

}
