#ifndef H_KAZACHTKOM_FUNCALL
#define H_KAZACHTKOM_FUNCALL

#include <vector>
#include <memory>
#include <optional>
#include "FunCallArgument.h"
#include "Identifier.h"
namespace kazachTKOM{

class Environment;
class FunCallArgument;

class FunctionCall {
public:
    FunctionCall(std::unique_ptr<Identifier>, std::vector<std::unique_ptr<FunCallArgument>>);
    std::optional<Number> execute(Environment&); // Optionally evaluates to a value.
private:
    std::unique_ptr<Identifier> fun_name;
    std::vector<std::unique_ptr<FunCallArgument>> args;
};

}
#endif // H_KAZACHTKOM_FUNCALL
