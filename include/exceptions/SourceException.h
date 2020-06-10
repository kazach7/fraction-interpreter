#ifndef H_KAZACHTKOM_SOURCEEXC
#define H_KAZACHTKOM_SOURCEEXC

#include <exception>
namespace kazachTKOM{

class SourceException : public std::exception {
public:
    SourceException(const std::string& msg, unsigned int line_no, unsigned int char_no) {
        error_msg = "ERROR during file reading. Line: " + std::to_string(line_no)
                     + ". Character: " + std::to_string(char_no) + ". Message:\n" + msg;
    }
    virtual ~SourceException() {}
    virtual const char* what() const throw(){
        return error_msg.c_str();
    }
private:
    std::string error_msg;
};

}
#endif // H_KAZACHTKOM_SOURCEEXC
