#ifndef H_KAZACHTKOM_PARSEREXC
#define H_KAZACHTKOM_PARSEREXC

#include <exception>
namespace kazachTKOM{

class ParserException : public std::exception {
public:
    ParserException(const std::string& msg, unsigned int line_no, unsigned int char_no){
        error_msg = "ERROR during parsing. Line: " + std::to_string(line_no) +
                     + ". Character: " + std::to_string(char_no) + ". Message:\n" + msg;
    }
    virtual ~ParserException()
    {}
    virtual const char* what() const throw(){
        return error_msg.c_str();
    }
private:
    std::string error_msg;
};

}
#endif // H_KAZACHTKOM_PARSEREXC
