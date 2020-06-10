#ifndef H_KAZACHTKOM_PROGRAM
#define H_KAZACHTKOM_PROGRAM

#include <memory>
#include <optional>
#include "DeclarationsBlock.h"
#include "RunningBlock.h"
namespace kazachTKOM{

class Environment;
class DeclarationsBlock;
class RunningBlock;

class Program {
public:
    Program(std::unique_ptr<DeclarationsBlock>, std::unique_ptr<RunningBlock>);
    std::optional<std::string> execute(Environment&); // Optionally returns the execution result value.
private:
    std::unique_ptr<DeclarationsBlock> decl_block;
    std::unique_ptr<RunningBlock> run_block;
};

} // kazachTKOM
#endif // H_KAZACHTKOM_PROGRAM
