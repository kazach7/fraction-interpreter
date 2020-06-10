#include "../../include/modules/Parser.h"
#include "../../include/modules/Scanner.h"
#include "../../include/Token.h"
#include "../../include/exceptions/ParserException.h"
#include <memory>
#include <vector>
#include <algorithm>
namespace kazachTKOM {

using TokenType = Token::TOKEN_TYPE;

Parser::Parser(Scanner& scanner)
    : scanner(scanner)
{
    advance();
}

Parser::~Parser()
{}

void Parser::advance()
{
    token = scanner.get_token();
}

bool Parser::check_token_type(const TokenType t) const
{
    return token->type == t;
}
bool Parser::check_token_type(const std::vector<TokenType> v) const
{
    return std::any_of(v.begin(), v.end(), [this](TokenType t){return token->type == t;});
}
bool Parser::accept(const TokenType t)
{
    if (check_token_type(t)){
        advance();
        return true;
    }
    return false;
}
void Parser::expect(const TokenType t, const std::string& error_msg){
    if (!accept(t)){
        throw ParserException(error_msg, token->line_no, token->char_no);
    }
}

std::unique_ptr<Program> Parser::parse_program() {
    auto decl_block = declarations_block();
    auto run_block = running_block();
    return std::make_unique<Program>(std::move(decl_block), std::move(run_block));
}

std::unique_ptr<DeclarationsBlock> Parser::declarations_block() {
    std::vector<std::unique_ptr<VariableDeclaration>> var_declarations;
    std::vector<std::unique_ptr<FunctionDefinition>> fun_definitions;

    std::unique_ptr<VariableDeclaration> v;
    std::unique_ptr<FunctionDefinition> f;
    while ((v = variable_declaration()) || (f = function_definition())){
        if (v){
            var_declarations.push_back(std::move(v));
        }
        else {
            fun_definitions.push_back(std::move(f));
        }
    }

    return std::make_unique<DeclarationsBlock>(std::move(var_declarations), std::move(fun_definitions));
}

std::unique_ptr<RunningBlock> Parser::running_block() {
    expect(TokenType::T_START_KW, "Expected 'Start' keyword after declarations block.");
    auto stmt_block = statement_block();
    expect(TokenType::T_KONIECPROG_KW, "Expected 'KoniecProgramu' keyword at the end of the program.");
    expect(TokenType::T_EOF, "Expected no token after 'KoniecProgramu' keyword.");

    return std::make_unique<RunningBlock>(std::move(stmt_block));
}

std::unique_ptr<VariableDeclaration> Parser::variable_declaration()
{
    auto ident = identifier();
    if (!ident){
        return nullptr;
    }

    auto arithm_expr = variable_initial_value_expression();
    expect(TokenType::T_SEMIC, "Expected ';' after variable declaration.");

    return std::make_unique<VariableDeclaration>(std::move(ident), std::move(arithm_expr));
}
std::unique_ptr<ArithmeticExpression> Parser::variable_initial_value_expression()
{
    if (!accept(TokenType::T_ASSIGN)) {
        return nullptr;
    }
    auto arithm_expr = arithmetic_expr();
    if (!arithm_expr) {
        throw ParserException("Expected arithmetic expression after '='.", token->line_no, token->char_no);
    }
    return std::move(arithm_expr);
}
std::unique_ptr<FunctionDefinition> Parser::function_definition()
{
    if(!accept(TokenType::T_FUNKCJA_KW)){
        return nullptr;
    }

    auto ident = identifier();
    if (!ident) {
        throw ParserException("Expected identifier after 'Funkcja' keyword.", token->line_no, token->char_no);
    }
    expect(TokenType::T_LPAREN, "Expected '(' after function name.");
    auto params = function_param_list();
    expect(TokenType::T_RPAREN, "Expected ')' after parameters list.");
    auto stmt_block = statement_block();
    expect(TokenType::T_KONIEC_KW, "Expected 'Koniec' keyword at the end of the function body.");

    return std::make_unique<FunctionDefinition>(std::move(ident), std::move(params), std::move(stmt_block));
}

std::vector<std::string> Parser::function_param_list()
{
    std::vector<std::string> params;

    auto p = identifier();
    if (!p){
        return params;
    }
    params.push_back(p->get_value());
    while (accept(TokenType::T_COMMA)){
        if (!(p = identifier())){
            throw ParserException("Expected identifier after ','.", token->line_no, token->char_no);
        }
        params.push_back(p->get_value());
    }

    return params;
}

std::unique_ptr<StatementBlock> Parser::statement_block()
{
    std::vector<std::unique_ptr<Statement>> statements;

    std::unique_ptr<Statement> stmt;
    while ((stmt = assignment_or_funcall_or_vardecl()) || (stmt = stdout_print()) ||
           (stmt = stdin_get()) || (stmt = if_else()) || (stmt = while_loop()) ||
           (stmt = return_statement()))
    {
        statements.push_back(std::move(stmt));
    }

    return std::make_unique<StatementBlock>(std::move(statements));
}

std::unique_ptr<Statement> Parser::assignment_or_funcall_or_vardecl()
{
    auto ident = identifier();
    if (!ident){
        return nullptr;
    }

    if (auto stmt = assignment_tail(std::make_unique<Identifier>(*ident)); stmt){
        return std::move(stmt);
    }

    if (auto fun_call = funcall_tail(std::make_unique<Identifier>(*ident)); fun_call){
        expect(TokenType::T_SEMIC, "Expected ';' after function call.");
        // Wrap the function call (technically an expression) into a statement.
        return std::make_unique<FunCallStatement>(std::move(fun_call));
    }

    if (accept(TokenType::T_SEMIC)){
        return std::make_unique<VariableDeclaration>(std::move(ident), nullptr);
    }

    return nullptr;
}
std::unique_ptr<Assignment> Parser::assignment_tail(std::unique_ptr<Identifier> ident)
{
    if (!check_token_type({TokenType::T_ASSIGN, TokenType::T_ADDASSIGN, TokenType::T_SUBASSIGN,
                           TokenType::T_MULTASSIGN, TokenType::T_DIVASSIGN})){
        return nullptr;
    }

    auto oper = token->value;
    advance();

    auto arithm_expr = arithmetic_expr();
    if (!arithm_expr){
        throw ParserException("Expected arithmetic expression after assignment operator.", token->line_no, token->char_no);
    };
    expect(TokenType::T_SEMIC, "Expected ';' after assignment.");

    return std::make_unique<Assignment>(std::move(ident), std::move(oper), std::move(arithm_expr));
}
std::unique_ptr<FunctionCall> Parser::funcall_tail(std::unique_ptr<Identifier> ident)
{
    if (!accept(TokenType::T_LPAREN)){
        return nullptr;
    }

    auto args = function_call_arg_list();
    expect(TokenType::T_RPAREN, "Expected ')' after call parameters list.");

    return std::make_unique<FunctionCall>(std::move(ident), std::move(args));
}
std::vector<std::unique_ptr<FunCallArgument>> Parser::function_call_arg_list()
{
    std::vector<std::unique_ptr<FunCallArgument>> args;

    auto p = fun_call_parameter();
    if (!p){
        return args;
    }
    args.push_back(std::move(p));
    while (accept(TokenType::T_COMMA)){
        if (!(p = fun_call_parameter())){
            throw ParserException("Expected function call parameter after ','.", token->line_no, token->char_no);
        }
        args.push_back(std::move(p));
    }

    return args;
}
std::unique_ptr<StdoutPrint> Parser::stdout_print()
{
    if (!accept(TokenType::T_WYPISZ_KW)){
        return nullptr;
    }

    std::unique_ptr<ArithmeticExpression> expr;
    auto str = literal(TokenType::T_STRING);
    if (!str && !(expr = arithmetic_expr())){
        throw ParserException("Expected string or arithmetic expression after 'Wypisz' keyword.",
                              token->line_no, token->char_no);
    }
    expect(TokenType::T_SEMIC, "Expected ';' after print statement.");

    return !str ? std::make_unique<StdoutPrint>(std::move(expr))
                : std::make_unique<StdoutPrint>(std::move(*str));
}
std::unique_ptr<StdinGet> Parser::stdin_get()
{
    if (!accept(TokenType::T_POBIERZ_KW)){
        return nullptr;
    }

    auto ident = identifier();
    if (!ident){
        throw ParserException("Expected identifier after 'Pobierz' keyword.", token->line_no, token->char_no);
    }
    expect(TokenType::T_SEMIC, "Expected ';' after stdin-reading statement.");

    return std::make_unique<StdinGet>(std::move(ident));
}
std::unique_ptr<IfElse> Parser::if_else()
{
    if (!accept(TokenType::T_JEZELI_KW)){
        return nullptr;
    }
    expect(TokenType::T_LPAREN, "Expected '(' after 'Jezeli' keyword.");

    auto cond = condition();
    if (!cond){
        throw ParserException("Expected condition after '('.", token->line_no, token->char_no);
    }
    expect(TokenType::T_RPAREN, "Expected ')' after condition.");

    auto true_block = statement_block();
    auto false_block = accept(TokenType::T_PRZECIWNIE_KW) ? statement_block() : nullptr;

    expect(TokenType::T_KONIEC_KW, "Expected 'Koniec' keyword at the end of the if-else statement.");

    return std::make_unique<IfElse>(std::move(cond), std::move(true_block), std::move(false_block));
}
std::unique_ptr<WhileLoop> Parser::while_loop()
{
    if (!accept(TokenType::T_DOPOKI_KW)){
        return nullptr;
    }
    expect(TokenType::T_LPAREN, "Expected '(' after 'Dopoki' keyword.");

    auto cond = condition();
    if (!cond){
        throw ParserException("Expected condition after '('.", token->line_no, token->char_no);
    }
    expect(TokenType::T_RPAREN, "Expected ')' after condition.");
    auto stmt_block = statement_block();
    expect(TokenType::T_KONIEC_KW, "Expected 'Koniec' keyword at the end of the while loop.");

    return std::make_unique<WhileLoop>(std::move(cond), std::move(stmt_block));
}
std::unique_ptr<ReturnStatement> Parser::return_statement()
{
    if (!accept(TokenType::T_ZWROC_KW)){
        return nullptr;
    }
    auto expr = arithmetic_expr();
    expect(TokenType::T_SEMIC, "Expected ';' after return statement.");

    return std::make_unique<ReturnStatement>(std::move(expr));
}

std::unique_ptr<ArithmeticExpression> Parser::arithmetic_expr()
{
    auto mult_expr = multiplicative_expr();
    if (!mult_expr){
        return nullptr;
    }

    std::vector<std::unique_ptr<MultiplicativeExpression>> expressions;
    std::vector<std::string> operators;
    expressions.push_back(std::move(mult_expr));

    while (check_token_type({TokenType::T_PLUS, TokenType::T_MINUS})){
        operators.push_back(token->value);
        advance();
        if (!(mult_expr = multiplicative_expr())){
            throw ParserException("Expected multiplicative expression after additive operator.", token->line_no, token->char_no);
        }
        expressions.push_back(std::move(mult_expr));
    }

    return std::make_unique<ArithmeticExpression>(std::move(expressions), std::move(operators));
}
std::unique_ptr<MultiplicativeExpression> Parser::multiplicative_expr()
{
    auto mult = multiplicable();
    if (!mult){
        return nullptr;
    }

    std::vector<std::unique_ptr<Multiplicable>> expressions;
    std::vector<std::string> operators;
    expressions.push_back(std::move(mult));

    while (check_token_type({TokenType::T_MULT, TokenType::T_DIV})){
        operators.push_back(token->value);
        advance();
        if (!(mult = multiplicable())){
            throw ParserException("Expected multiplicable expression after multiplicative operator.", token->line_no, token->char_no);
        }
        expressions.push_back(std::move(mult));
    }
    return std::make_unique<MultiplicativeExpression>(std::move(expressions), std::move(operators));
}
std::unique_ptr<Multiplicable> Parser::multiplicable()
{
    unsigned int line_no = token->line_no;
    unsigned int char_no = token->char_no;

    bool is_negative = accept(TokenType::T_MINUS);

    if (auto braced = braced_multiplicable(is_negative, line_no, char_no); braced){
        return std::move(braced);
    }
    if (auto number = literal(TokenType::T_NUMBER); number){
        return std::make_unique<Multiplicable>(is_negative, std::stol(*number), line_no, char_no);
    }
    if (auto ident = identifier(); ident){
        if (auto fun_call = funcall_tail(std::make_unique<Identifier>(*ident)); fun_call){
            return std::make_unique<Multiplicable>(is_negative, std::move(fun_call), line_no, char_no);
        }
        return std::make_unique<Multiplicable>(is_negative, std::move(ident), line_no, char_no);
    }

    return nullptr;
}
std::unique_ptr<Multiplicable> Parser::braced_multiplicable(const bool& is_negative, const unsigned int& line_no,
                                                            const unsigned int& char_no)
{
    if (!accept(TokenType::T_LPAREN)){
        return nullptr;
    }

    auto arithm_expr = arithmetic_expr();
    if (!arithm_expr){
        throw ParserException("Expected arithmetic expression after '('.", token->line_no, token->char_no);
    }
    expect(TokenType::T_RPAREN, "Expected ')' after arithmetic expression.");

    return std::make_unique<Multiplicable>(is_negative, std::move(arithm_expr), line_no, char_no);
}

std::unique_ptr<LogicalExpression> Parser::logical_expr()
{
    auto expr = and_expr();
    if (!expr){
        return nullptr;
    }

    std::vector<std::unique_ptr<AndExpression>> expressions;
    expressions.push_back(std::move(expr));

    while (accept(TokenType::T_OR_OP)){
        if (!(expr = and_expr())){
            throw ParserException("Expected expression after '||'.", token->line_no, token->char_no);
        }
        expressions.push_back(std::move(expr));
    }

    return std::make_unique<LogicalExpression>(std::move(expressions));
}
std::unique_ptr<AndExpression> Parser::and_expr()
{
    auto expr = equality_expr();
    if (!expr){
        return nullptr;
    }

    std::vector<std::unique_ptr<EqualityExpression>> expressions;
    expressions.push_back(std::move(expr));

    while (accept(TokenType::T_AND_OP)){
        if (!(expr = equality_expr())){
            throw ParserException("Expected expression after '&&'.", token->line_no, token->char_no);
        }
        expressions.push_back(std::move(expr));
    }

    return std::make_unique<AndExpression>(std::move(expressions));
}
std::unique_ptr<EqualityExpression> Parser::equality_expr()
{
    auto expr = relational_expr();
    if (!expr){
        return nullptr;
    }

    std::vector<std::unique_ptr<RelationalExpression>> expressions;
    std::vector<std::string> operators;
    expressions.push_back(std::move(expr));

    while (check_token_type({TokenType::T_EQUAL, TokenType::T_UNEQUAL})){
        operators.push_back(token->value);
        advance();
        if (!(expr = relational_expr())){
            throw ParserException("Expected expression after equality operator.", token->line_no, token->char_no);
        }
        expressions.push_back(std::move(expr));
    }

    return std::make_unique<EqualityExpression>(std::move(expressions), std::move(operators));
}
std::unique_ptr<RelationalExpression> Parser::relational_expr()
{
    auto expr = comparable();
    if (!expr){
        return nullptr;
    }

    std::vector<std::unique_ptr<Comparable>> expressions;
    std::vector<std::string> operators;
    expressions.push_back(std::move(expr));

    while (check_token_type({TokenType::T_LESS, TokenType::T_GREATER,
                             TokenType::T_LESSEQ, TokenType::T_GREATEQ})){
        operators.push_back(token->value);
        advance();
        if(!(expr = comparable())){
            throw ParserException("Expected expression after relational operator.", token->line_no, token->char_no);
        }
        expressions.push_back(std::move(expr));
    }

    return std::make_unique<RelationalExpression>(std::move(expressions), std::move(operators));
}
std::unique_ptr<Comparable> Parser::comparable()
{
    if (check_token_type({TokenType::T_UNARYNEGAT, TokenType::T_LPAREN})){
        bool is_negated = accept(TokenType::T_UNARYNEGAT);
        if (is_negated){
            expect(TokenType::T_LPAREN, "Expected '(' after '!'.");
        }
        else {
            accept(TokenType::T_LPAREN);
        }
        auto logic_expr = logical_expr();
        if (!logic_expr){
            throw ParserException("Expected expression after '('.", token->line_no, token->char_no);
        }
        expect(TokenType::T_RPAREN, "Expected ')' after expression.");

        return std::make_unique<Comparable>(is_negated, std::move(logic_expr));
    }

    if (auto arithm_expr = arithmetic_expr(); arithm_expr){
        return std::make_unique<Comparable>(std::move(arithm_expr));
    }

    return nullptr;
}

std::unique_ptr<FunCallArgument> Parser::fun_call_parameter()
{
    auto expr = arithmetic_expr();
    if (!expr){
        return nullptr;
    }
    return std::make_unique<FunCallArgument>(std::move(expr));
}
std::unique_ptr<Condition> Parser::condition()
{
    auto expr = logical_expr();
    if (!expr){
        return nullptr;
    }
    return std::make_unique<Condition>(std::move(expr));
}

std::unique_ptr<Identifier> Parser::identifier()
{
    if (!check_token_type(TokenType::T_IDENT)){
        return nullptr;
    }
    auto value = token->value;
    auto line_no = token->line_no;
    auto char_no = token->char_no;
    advance();
    return std::make_unique<Identifier>(value, line_no, char_no);
}
std::optional<std::string> Parser::literal(const TokenType type)
{
    if (!check_token_type(type)){
        return std::nullopt;
    }
    auto value = token->value;
    advance();
    return value;
}

} // kazachTKOM
