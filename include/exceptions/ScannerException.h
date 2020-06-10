#ifndef H_KAZACHTKOM_SCANNEREXC
#define H_KAZACHTKOM_SCANNEREXC

#include <exception>
namespace kazachTKOM{

class ScannerException : public std::exception {
public:
    ScannerException(const std::string& msg, unsigned int line_no, unsigned int char_no) {
        error_msg = "ERROR during lexical analysis. Line: " + std::to_string(line_no)
                     + ". Character: " + std::to_string(char_no) + ". Message:\n" + msg;
    }
    virtual ~ScannerException() {}
    virtual const char* what() const throw() {
        return error_msg.c_str();
    }
private:
    std::string error_msg;
};

}
#endif // H_KAZACHTKOM_SCANNEREXC
