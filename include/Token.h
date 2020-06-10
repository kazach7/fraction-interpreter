#ifndef H_KAZACHTKOM_TOKEN
#define H_KAZACHTKOM_TOKEN

#include <string>
namespace kazachTKOM {

class Token {
public:
    enum TOKEN_TYPE {
        T_START_KW, T_KONIECPROG_KW, T_KONIEC_KW, T_FUNKCJA_KW,
        T_WYPISZ_KW, T_POBIERZ_KW, T_JEZELI_KW, T_PRZECIWNIE_KW,
        T_DOPOKI_KW, T_ZWROC_KW,
        T_IDENT, T_NUMBER, T_STRING,
        T_PLUS, T_MINUS, T_MULT, T_DIV,
        T_ADDASSIGN, T_SUBASSIGN, T_MULTASSIGN, T_DIVASSIGN,
        T_LESS, T_GREATER, T_LESSEQ, T_GREATEQ,
        T_ASSIGN, T_EQUAL, T_UNARYNEGAT, T_UNEQUAL,
        T_AND_OP, T_OR_OP, T_LPAREN, T_RPAREN, T_COMMA, T_SEMIC, T_EOF
    };

    Token(const TOKEN_TYPE type, const std::string& value,
          const unsigned int line_no, const unsigned int char_no)
          : type(type), value(value), line_no(line_no), char_no(char_no)
    {}

    ~Token() {}

    enum TOKEN_TYPE type;
    std::string value;
    unsigned int line_no;
    unsigned int char_no;
};

}
#endif // H_KAZACHTKOM_TOKEN
