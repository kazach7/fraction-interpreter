#ifndef H_KAZACHTKOM_RUNTIMEEXC
#define H_KAZACHTKOM_RUNTIMEEXC

#include <exception>
#include <string>
namespace kazachTKOM{

class RuntimeException : public std::exception {
public:
    RuntimeException(const std::string& msg, unsigned int line_no, unsigned int char_no){
        error_msg = "ERROR during runtime. Line: " + std::to_string(line_no)
                     + ". Character: " + std::to_string(char_no) + ". Message:\n" + msg;
    }
    virtual ~RuntimeException()
    {}
    virtual const char* what() const throw(){
        return error_msg.c_str();
    }
private:
    std::string error_msg;
};

}
#endif // H_KAZACHTKOM_RUNTIME
