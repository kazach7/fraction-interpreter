#ifndef H_KAZACHTKOM_STMTBLOCK
#define H_KAZACHTKOM_STMTBLOCK

#include "Statement.h"
#include <vector>
#include <memory>
namespace kazachTKOM{

class Environment;

class StatementBlock : public Statement {
public:
    StatementBlock(std::vector<std::unique_ptr<Statement>>);
    void execute(Environment&);
private:
    std::vector<std::unique_ptr<Statement>> statements;
};

}
#endif // H_KAZACHTKOM_STMTBLOCK
