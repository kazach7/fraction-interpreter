#include "../../include/program-tree/RunningBlock.h"
#include "../../include/environment/Environment.h"
#include "../../include/program-tree/Number.h"
namespace kazachTKOM{

RunningBlock::RunningBlock(std::unique_ptr<StatementBlock> b)
    : stmt_block(std::move(b)) {}

std::optional<std::string> RunningBlock::execute(Environment& env){
    env.make_function_scope();
    stmt_block->execute(env);
    auto returned_value = env.get_returned_value();
    env.destroy_function_scope();

    std::string result;
    if (returned_value){
        result += std::to_string(returned_value->get_numerator());
        auto denominator = returned_value->get_denominator();
        if (denominator != 1){
            result += "/" + std::to_string(denominator);
        }
        return {result};
    }
    return std::nullopt;
}

}
