#ifndef H_KAZACHTKOM_STDIOMANAGER
#define H_KAZACHTKOM_STDIOMANAGER

#include <string>
namespace kazachTKOM{

class StdIOManager
{
public:
    void print_on_stdout(const std::string&);
    std::string get_from_stdin();
};

}
#endif // H_KAZACHTKOM_STDIOMANAGER
