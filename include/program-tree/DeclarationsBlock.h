#ifndef H_KAZACHTKOM_DECLBLOCK
#define H_KAZACHTKOM_DECLBLOCK

#include <vector>
#include <memory>
#include "VariableDeclaration.h"
#include "FunctionDefinition.h"
namespace kazachTKOM{

class Environment;
class VariableDeclaration;
class FunctionDefinition;;

class DeclarationsBlock
{
public:
    DeclarationsBlock(std::vector<std::unique_ptr<VariableDeclaration>>,
                      std::vector<std::unique_ptr<FunctionDefinition>>);
    void execute(Environment&);
private:
    std::vector<std::unique_ptr<VariableDeclaration>> var_declarations;
    std::vector<std::unique_ptr<FunctionDefinition>> fun_definitions;
};

}
#endif // H_KAZACHTKOM_DECLBLOCK
