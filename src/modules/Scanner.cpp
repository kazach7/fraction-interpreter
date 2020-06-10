#include "../../include/modules/Scanner.h"
#include "../../include/modules/Source.h"
#include "../../include/Token.h"
#include "../../include/exceptions/ScannerException.h"
#include <utility>
namespace kazachTKOM {

using TokenType = Token::TOKEN_TYPE;

Scanner::Scanner(Source& source,
                  std::initializer_list<std::pair<const std::string, Token::TOKEN_TYPE>> init_list)
                  : source(source), keywords_map(init_list)
{
    ch = source.get_char();
}

Scanner::~Scanner()
{}

std::unique_ptr<Token> Scanner::get_token()
{
    while (isspace(ch)) advance();
    token_line_no = source.get_line_no();
    token_char_no = source.get_char_no();

    std::optional<Token> token;
    if (!(token = try_to_build_keyw_or_ident()) &&
        !(token = try_to_build_number()) &&
        !(token = try_to_build_string()) &&
        !(token = try_to_build_operator_with_optional_equal_sign()) &&
        !(token = try_to_build_other_operator_or_punctuation_mark()) &&
        !(token = try_to_build_EOF())
    ){
        std::string msg = "Unrecognizable character (";
        msg += std::to_string(static_cast<int>(ch)) + ").";
        throw ScannerException(msg, token_line_no, token_char_no);
    }

    return std::make_unique<Token>(*token);
}

void Scanner::advance()
{
    ch = source.get_char();
}

std::optional<Token> Scanner::try_to_build_keyw_or_ident()
{
    if (!isalpha(ch) && ch != '_'){
        return std::nullopt;
    }
    std::string value;
    int n = 0;
    do{
        if (++n > MAX_CHARACTERS){
            std::string msg = "Maximum token lenght (" + std::to_string(MAX_CHARACTERS) + ") exceeded"
                               + " while building a keyword/identifier.";
            throw ScannerException(msg, source.get_line_no(), source.get_char_no());
        }
        value += ch;
        advance();
    } while (isalnum(ch) || ch == '_');

    TokenType type;
    auto it = keywords_map.find(value);
    if (it != keywords_map.end()){
        type = it->second;
    }
    else {
        type = TokenType::T_IDENT;
    }

    return Token(type, value, token_line_no, token_char_no);
}
std::optional<Token> Scanner::try_to_build_number()
{
    if (!isdigit(ch)){
        return std::nullopt;
    }
    std::string value;
    if (ch == '0'){
        value += ch;
        advance();
    }
    else {
        int n = 0;
        do {
            if (++n > MAX_DIGITS){
                std::string msg = "Maximum no. of digits (" + std::to_string(MAX_DIGITS)
                                   + ") exceeded while building a number.";
                throw ScannerException(msg, source.get_line_no(), source.get_char_no());
            }
            value += ch;
            advance();
        } while (isdigit(ch));
    }

    return Token(TokenType::T_NUMBER, value, token_line_no, token_char_no);
}
std::optional<Token> Scanner::try_to_build_string()
{
    if (ch != '\"'){
        return std::nullopt;
    }
    advance(); // Omit '"'.
    std::string value;
    int n = 0;
    while (ch != '"' && (isprint(ch) || isspace(ch))) {
        if (ch == '\\'){
            advance();
            switch (ch){
            case '\\': ch = '\\'; break;
            case 'n': ch = '\n'; break;
            case 't': ch = '\t'; break;
            case '"': ch = '\"'; break;
            default: continue;
            }
        }
        if (++n > MAX_CHARACTERS){
            std::string msg = "Maximum token lenght (" + std::to_string(MAX_CHARACTERS)
                               + ") exceeded while building a string.";
            throw ScannerException(msg, source.get_line_no(), source.get_char_no());
        }
        value += ch;
        advance();
    }
    if (ch == '"'){
        advance();
    }

    return Token(TokenType::T_STRING, value, token_line_no, token_char_no);
}
std::optional<Token> Scanner::try_to_build_operator_with_optional_equal_sign()
{
    std::pair<TokenType, TokenType> type;
    switch (ch){
    case '+': type = std::make_pair(TokenType::T_PLUS, TokenType::T_ADDASSIGN); break;
    case '-': type = std::make_pair(TokenType::T_MINUS, TokenType::T_SUBASSIGN); break;
    case '*': type = std::make_pair(TokenType::T_MULT, TokenType::T_MULTASSIGN); break;
    case '/': type = std::make_pair(TokenType::T_DIV, TokenType::T_DIVASSIGN); break;
    case '<': type = std::make_pair(TokenType::T_LESS, TokenType::T_LESSEQ); break;
    case '>': type = std::make_pair(TokenType::T_GREATER, TokenType::T_GREATEQ); break;
    case '=': type = std::make_pair(TokenType::T_ASSIGN, TokenType::T_EQUAL); break;
    case '!': type = std::make_pair(TokenType::T_UNARYNEGAT, TokenType::T_UNEQUAL); break;
    default: return std::nullopt;
    }
    std::string value;
    value += ch;
    advance();

    auto which = [&]() {
        if (ch == '='){
            value += ch;
            advance();
            return std::get<1>(type);
        }
        else return std::get<0>(type);
    };

    return Token(which(), value, token_line_no, token_char_no);
}
std::optional<Token> Scanner::try_to_build_other_operator_or_punctuation_mark()
{
    TokenType type;
    switch (ch){
    case '&': type = TokenType::T_AND_OP; break;
    case '|': type = TokenType::T_OR_OP; break;
    case '(': type = TokenType::T_LPAREN; break;
    case ')': type = TokenType::T_RPAREN; break;
    case ',': type = TokenType::T_COMMA; break;
    case ';': type = TokenType::T_SEMIC; break;
    default: return std::nullopt;
    }

    if (type == TokenType::T_AND_OP || type == TokenType::T_OR_OP){
        char temp = ch;
        advance();
        if (ch != temp){
            std::string msg = "Unexpected character while building operator ";
            msg += temp;
            msg += temp;
            throw ScannerException(msg, source.get_line_no(), source.get_char_no());
        }
    }
    advance();

    return Token(type, std::string(), token_line_no, token_char_no);
}
std::optional<Token> Scanner::try_to_build_EOF(){
    if (ch != 3){
        return std::nullopt;
    }
    return Token(TokenType::T_EOF, std::string(), token_line_no, token_char_no);
}

} //kazachTKOM
