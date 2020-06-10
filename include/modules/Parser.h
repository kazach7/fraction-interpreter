#ifndef H_KAZACHTKOM_PARSER
#define H_KAZACHTKOM_PARSER

#include "../Token.h"
#include "../program-tree/program-tree-includes.h"
#include <vector>
#include <optional>
namespace kazachTKOM{

class Scanner;

/**
 * The module performing syntactic analysis.
 * Builds the program syntax tree, returns the root node ready to execute.
 */
class Parser {
public:
    Parser(Scanner& scanner);
    ~Parser();
    std::unique_ptr<Program> parse_program();

private:
    std::unique_ptr<Token> token; // Next token to consume.
    Scanner& scanner; // The lexer to get the tokens from.

    void advance(); // Get next token.
    bool check_token_type(const Token::TOKEN_TYPE) const;      // Compare the type of the next token to the argument.
    bool check_token_type(const std::vector<Token::TOKEN_TYPE>) const;
    bool accept (const Token::TOKEN_TYPE);                     // Consume the next token if it matches the argument.
    void expect(const Token::TOKEN_TYPE, const std::string&);  // Consume the next token if it matches the argument,
                                                               // otherwise call error.

    // Functions creating the program tree.
    std::unique_ptr<DeclarationsBlock> declarations_block();
    std::unique_ptr<RunningBlock> running_block();

    std::unique_ptr<VariableDeclaration> variable_declaration();
    std::unique_ptr<ArithmeticExpression> variable_initial_value_expression();
    std::unique_ptr<FunctionDefinition> function_definition();
    std::vector<std::string> function_param_list();

    std::unique_ptr<StatementBlock> statement_block();

    std::unique_ptr<Statement> assignment_or_funcall_or_vardecl();
    std::unique_ptr<Assignment> assignment_tail(std::unique_ptr<Identifier>);
    std::unique_ptr<FunctionCall> funcall_tail(std::unique_ptr<Identifier>);
    std::vector<std::unique_ptr<FunCallArgument>> function_call_arg_list();
    std::unique_ptr<StdoutPrint> stdout_print();
    std::unique_ptr<StdinGet> stdin_get();
    std::unique_ptr<IfElse> if_else();
    std::unique_ptr<WhileLoop> while_loop();
    std::unique_ptr<ReturnStatement> return_statement();

    std::unique_ptr<LogicalExpression> logical_expr();
    std::unique_ptr<AndExpression> and_expr();
    std::unique_ptr<EqualityExpression> equality_expr();
    std::unique_ptr<RelationalExpression> relational_expr();
    std::unique_ptr<Comparable> comparable();

    std::unique_ptr<ArithmeticExpression> arithmetic_expr();
    std::unique_ptr<MultiplicativeExpression> multiplicative_expr();
    std::unique_ptr<Multiplicable> multiplicable();
    std::unique_ptr<Multiplicable> braced_multiplicable(const bool&, const unsigned int&, const unsigned int&);

    std::unique_ptr<FunCallArgument> fun_call_parameter();
    std::unique_ptr<Condition> condition();
    std::unique_ptr<Identifier> identifier();
    std::optional<std::string> literal(const Token::TOKEN_TYPE);
};

}
#endif // H_KAZACHTKOM_PARSER
