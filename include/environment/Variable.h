#ifndef H_KAZACHTKOM_VARIABLE
#define H_KAZACHTKOM_VARIABLE

#include <string>
#include "../program-tree/Number.h"
namespace kazachTKOM{

class Number;

class Variable {
public:
    Variable (const std::string&, const Number);
    const std::string get_name() const;
    Number get_value() const;
    void set_value(const Number);
private:
    const std::string identifier;
    Number value;
};

}
#endif // H_KAZACHTKOM_VARIABLE
