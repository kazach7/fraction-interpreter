#ifndef H_KAZACHTKOM_STDINGET
#define H_KAZACHTKOM_STDINGET

#include <string>
#include <memory>
#include "Statement.h"
#include "Identifier.h"
#include "Number.h"
namespace kazachTKOM{

class Environment;

class StdinGet : public Statement {
public:
    StdinGet(std::unique_ptr<Identifier>);
    void execute(Environment&);
private:
    std::unique_ptr<Identifier> var_name;
    Number parse_input(const std::string&);
};

}
#endif // H_KAZACHTKOM_STDINGET
