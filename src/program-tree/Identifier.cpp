#include "../../include/program-tree/Identifier.h"
namespace kazachTKOM{

Identifier::Identifier(const std::string& v, const unsigned int line, const unsigned int ch)
    : value(v), line_no(line), char_no(ch) {}

const std::string Identifier::get_value() const {
    return value;
}
const unsigned int Identifier::get_line_no() const {
    return line_no;
}
const unsigned int Identifier::get_char_no() const {
    return char_no;
}

}
