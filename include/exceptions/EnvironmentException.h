#ifndef H_KAZACHTKOM_ENVIRONEXC
#define H_KAZACHTKOM_ENVIRONEXC

#include <exception>
namespace kazachTKOM{

class EnvironmentException : public std::exception {
public:
    EnvironmentException(const std::string& msg){
        error_msg = msg;
    }
    virtual ~EnvironmentException()
    {}
    virtual const char* what() const throw(){
        return error_msg.c_str();
    }
private:
    std::string error_msg;
};

}
#endif // H_KAZACHTKOM_ENVIRONEXC
