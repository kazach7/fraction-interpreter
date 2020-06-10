#ifndef H_KAZACHTKOM_RUNBLOCK
#define H_KAZACHTKOM_RUNBLOCK

#include <memory>
#include <optional>
#include <string>
#include "StatementBlock.h"
namespace kazachTKOM{

class Environment;
class StatementBlock;

class RunningBlock {
public:
    RunningBlock(std::unique_ptr<StatementBlock>);
    std::optional<std::string> execute(Environment&); // Optionally returns the execution result value.
private:
    std::unique_ptr<StatementBlock> stmt_block;
};

}
#endif // H_KAZACHTKOM_RUNBLOCK
