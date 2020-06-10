#include "../../include/environment/Variable.h"
namespace kazachTKOM{

Variable::Variable(const std::string& n, const Number v = Number(0, 1))
    : identifier(n), value(v) {}

const std::string Variable::get_name() const{
    return identifier;
}
Number Variable::get_value() const{
    return value;
}
void Variable::set_value(const Number v){
    value = v;
}
}
