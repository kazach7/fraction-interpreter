#ifndef H_KAZACHTKOM_WHILELOOP
#define H_KAZACHTKOM_WHILELOOP

#include "Statement.h"
#include "Condition.h"
#include "StatementBlock.h"
#include <memory>
namespace kazachTKOM{

class Condition;
class StatementBlock;

class WhileLoop : public Statement {
public:
    WhileLoop(std::unique_ptr<Condition>, std::unique_ptr<StatementBlock>);
    void execute(Environment&);
private:
    std::unique_ptr<Condition> cond;
    std::unique_ptr<StatementBlock> stmt_block;
};

}
#endif // H_KAZACHTKOM_WHILELOOP
