#ifndef H_KAZACHTKOM_FUNCTIONDEF
#define H_KAZACHTKOM_FUNCTIONDEF

#include <vector>
#include <memory>
#include "StatementBlock.h"
#include "Identifier.h"
namespace kazachTKOM{

class Environment;
class StatementBlock;

class FunctionDefinition {
public:
    FunctionDefinition(std::unique_ptr<Identifier>, const std::vector<std::string>&,
                       std::unique_ptr<StatementBlock>);
    void execute(Environment&);
private:
    std::unique_ptr<Identifier> fun_name;
    std::vector<std::string> params;
    std::unique_ptr<StatementBlock> stmt_block;
};

}
#endif // H_KAZACHTKOM_FUNCTIONDEF
