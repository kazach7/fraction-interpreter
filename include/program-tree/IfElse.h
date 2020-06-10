#ifndef H_KAZACHTKOM_IFELSE
#define H_KAZACHTKOM_IFELSE

#include "Statement.h"
#include "Condition.h"
#include "StatementBlock.h"
#include <memory>
namespace kazachTKOM{

class Environment;

class IfElse : public Statement {
public:
    IfElse(std::unique_ptr<Condition>, std::unique_ptr<StatementBlock>,
           std::unique_ptr<StatementBlock>);
    void execute(Environment&);
private:
    std::unique_ptr<Condition> cond;
    std::unique_ptr<StatementBlock> true_block;
    std::unique_ptr<StatementBlock> false_block;
};

}
#endif // H_KAZACHTKOM_IFELSE
