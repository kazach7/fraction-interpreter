#include "../../include/program-tree/WhileLoop.h"
namespace kazachTKOM{

WhileLoop::WhileLoop(std::unique_ptr<Condition> c, std::unique_ptr<StatementBlock> b)
    : cond(std::move(c)), stmt_block(std::move(b)) {}

void WhileLoop::execute(Environment& env){
    while (cond->evaluate(env)){
        stmt_block->execute(env);
    }
}

}
