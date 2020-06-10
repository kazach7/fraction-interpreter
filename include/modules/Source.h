#ifndef H_KAZACHTKOM_SOURCE
#define H_KAZACHTKOM_SOURCE

#include <string>
namespace kazachTKOM {

/**
 * Abstraction of the source code.
 * Provides methods to get next character from the source and to get current reading position.
 */
class Source {
public:
    Source(std::istream&);
    ~Source();

    char get_char();      // Get next character.
    unsigned int get_line_no() const;
    unsigned int get_char_no() const;
private:
    std::istream& stream; // File to read from.
    char ch;              // Next character to return.
    unsigned int line_no; // Current line number.
    unsigned int char_no; // Current character in the line number.
    bool eof_reached;     // If eof already 'read' stop incrementing character position.
};

} // kazachTKOM
#endif // H_KAZACHTKOM_SOURCE
