#include "../../include/program-tree/DeclarationsBlock.h"
#include "../../include/environment/Environment.h"
namespace kazachTKOM{

DeclarationsBlock::DeclarationsBlock(std::vector<std::unique_ptr<VariableDeclaration>> v,
                                     std::vector<std::unique_ptr<FunctionDefinition>> f)
    : var_declarations(std::move(v)), fun_definitions(std::move(f)) {}

void DeclarationsBlock::execute(Environment& env){
    for (auto &var_decl : var_declarations){
        var_decl->execute(env);
    }
    for (auto &fun_def : fun_definitions){
        fun_def->execute(env);
    }
}

}
