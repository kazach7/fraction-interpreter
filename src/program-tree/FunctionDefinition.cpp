#include "../../include/program-tree/FunctionDefinition.h"
#include "../../include/environment/Function.h"
#include "../../include/environment/Environment.h"
#include "../../include/exceptions/EnvironmentException.h"
#include "../../include/exceptions/RuntimeException.h"
#include <algorithm>
namespace kazachTKOM{

FunctionDefinition::FunctionDefinition(std::unique_ptr<Identifier> n, const std::vector<std::string>& p,
                                       std::unique_ptr<StatementBlock> b)
    : fun_name(std::move(n)), params(p), stmt_block(std::move(b)) {}

void FunctionDefinition::execute(Environment& env){
    // Check if the paramters' names are unique.
    std::vector<std::string> temp(params);
    std::sort(temp.begin(), temp.end());
    if (std::unique(temp.begin(), temp.end()) != temp.end()){
        throw RuntimeException("Function parameters' names must be unique.", 
                               fun_name->get_line_no(), fun_name->get_char_no());
    }

    try {
        env.add_function(std::make_unique<Function>(fun_name->get_value(), params, stmt_block.get()));
    }
    catch (EnvironmentException& e) {
        throw RuntimeException(e.what(), fun_name->get_line_no(), fun_name->get_char_no());
    }
}

}
