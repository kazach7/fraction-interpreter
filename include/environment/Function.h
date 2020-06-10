#ifndef H_KAZACHTKOM_FUNCTION
#define H_KAZACHTKOM_FUNCTION

#include <vector>
#include <memory>
#include <optional>
#include "../program-tree/FunCallArgument.h"
#include "../program-tree/StatementBlock.h"
#include "../program-tree/Number.h"
#include "Environment.h"
namespace kazachTKOM{

class Function {
public:
    Function(const std::string&, const std::vector<std::string>&, StatementBlock*);
    std::optional<Number> call(std::vector<FunCallArgument*>&, Environment&); // Optionally returns a value.
    const std::string get_name() const;
    const int get_param_count() const;
private:
    const std::string fun_name;
    std::vector<std::string> params;
    StatementBlock* stmt_block;
};

}
#endif // H_KAZACHTKOM_FUNCTION
