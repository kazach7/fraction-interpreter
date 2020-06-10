#include "../../include/program-tree/Program.h"
#include "../../include/environment/Environment.h"
namespace kazachTKOM{

Program::Program(std::unique_ptr<DeclarationsBlock> d, std::unique_ptr<RunningBlock> r)
    : decl_block(std::move(d)), run_block(std::move(r)) {}

std::optional<std::string> Program::execute(Environment& env){
    decl_block->execute(env);
    return run_block->execute(env);
}

} // kazachTKOM
