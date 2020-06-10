#include "../../include/program-tree/StatementBlock.h"
#include "../../include/environment/Environment.h"
namespace kazachTKOM{

StatementBlock::StatementBlock(std::vector<std::unique_ptr<Statement>> s)
    : statements(std::move(s)) {}

void StatementBlock::execute(Environment& env){
    env.make_local_scope();
    for (auto &stmt : statements){
        stmt->execute(env);
        if (env.has_returned()){ // If this was a return stmt or this was a stmt block with a return stmt in it.
            break;
        }
    }
    env.destroy_local_scope();
}

}
