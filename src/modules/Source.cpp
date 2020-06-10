#include "../../include/modules/Source.h"
#include "../../include/exceptions/SourceException.h"
#include <istream>
namespace kazachTKOM {

Source::Source(std::istream& stream)
    : stream(stream), line_no(1), char_no(0), eof_reached(false)
{}

Source::~Source()
{}

char Source::get_char() {
    try {
        stream.read(&ch, sizeof(char));
        if (stream.eof()){
            if (!eof_reached){
                ++char_no;
                eof_reached = true;
            }
            ch = 3;
        }
        else{
            if (ch == '\n'){
                ++line_no;
                char_no = 0;
            }
            else {
                ++char_no;
            }
        }
    }
    catch (std::exception& e){
        throw SourceException(e.what(), line_no, char_no);
    }
    return ch;
}
unsigned int Source::get_line_no() const {
    return line_no;
}
unsigned int Source::get_char_no() const {
    return char_no;
}

} // kazachTKOM
