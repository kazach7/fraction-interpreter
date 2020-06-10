#ifndef H_KAZACHTKOM_SCANNER
#define H_KAZACHTKOM_SCANNER

#include <map>
#include <memory>
#include <optional>
#include "../Token.h"
namespace kazachTKOM {

class Source;

/**
 * The module performing lexical analysis.
 * Builds tokens from characters obtained from Source.
 */
class Scanner
{
public:
    Scanner(Source& source,
              std::initializer_list<std::pair<const std::string, Token::TOKEN_TYPE>> initializer_list);
    ~Scanner();

    static const int MAX_CHARACTERS = 1024; // Maximum no. of characters in a token value (keyw/ident/string).
    static const int MAX_DIGITS = 9;        // Maximum no. of digits in a number token.

    std::unique_ptr<Token> get_token();
private:
    char ch;              // The character to be consumed next.
    Source& source;       // The source abstraction to read the characters from.
    unsigned int token_line_no; // Token beggining line number.
    unsigned int token_char_no; // Token beggining character in line number.
    std::map<std::string, Token::TOKEN_TYPE> keywords_map; // All possible keywords.

    void advance(); // Get next character from the source.
    std::optional<Token> try_to_build_keyw_or_ident();
    std::optional<Token> try_to_build_number();
    std::optional<Token> try_to_build_string();
    std::optional<Token> try_to_build_operator_with_optional_equal_sign();
    std::optional<Token> try_to_build_other_operator_or_punctuation_mark();
    std::optional<Token> try_to_build_EOF();
};

}
#endif // H_KAZACHTKOM_SCANNER
