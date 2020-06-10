#ifndef H_KAZACHTKOM_IDENTIFIER
#define H_KAZACHTKOM_IDENTIFIER
#include <string>
namespace kazachTKOM{

class Identifier
{
public:
    Identifier(const std::string&, const unsigned int, const unsigned int);
    const std::string get_value() const;
    const unsigned int get_line_no() const;
    const unsigned int get_char_no() const;

private:
    const std::string value;
    const unsigned int line_no;
    const unsigned int char_no;
};

}
#endif // H_KAZACHTKOM_IDENTIFIER
