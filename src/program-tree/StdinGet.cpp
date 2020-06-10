#include "../../include/program-tree/StdinGet.h"
#include "../../include/environment/Environment.h"
#include "../../include/environment/Variable.h"
#include "../../include/exceptions/RuntimeException.h"
#include "../../include/modules/StdIOManager.h"
#include <iostream>
namespace kazachTKOM{

StdinGet::StdinGet(std::unique_ptr<Identifier> n)
    : var_name(std::move(n)) {}

void StdinGet::execute(Environment& env){
    Variable* var = env.get_variable(var_name->get_value());
    if (!var){
        throw RuntimeException("Variable undeclared.", var_name->get_line_no(), var_name->get_char_no());
    }

    StdIOManager iomanager;
    var->set_value(parse_input(iomanager.get_from_stdin()));
}

Number StdinGet::parse_input(const std::string& input)
{
    try{
        auto slash_pos = input.find('/');
        return Number(std::stol(input.substr(0, slash_pos)),
                        slash_pos == std::string::npos ?
                        1 : static_cast<unsigned>(std::stoi(input.substr(slash_pos+1))));
    }
    catch (std::exception& e){
        (void)e; // To avoid 'unused variable' warning.
        throw RuntimeException("Invalid stdin input.", var_name->get_line_no(), var_name->get_char_no());
    }/*
    if (slash_pos == std::string::npos){
        try {
            return std::stol(input);
        }
        catch (std::exception& e){
            throw RuntimeException(e.what(), var_name->get_line_no());
        }
    }
    else {
        if (slash_pos == input.size()-1){
            throw RuntimeException("Invalid stdin input - denominator can't be empty!",
                                   var_name->get_line_no());
        }
        else if (input.find('/', slash_pos+1) != std::string::npos){
            throw RuntimeException("Invalid stdin input - up to one slash allowed!",
                                   var_name->get_line_no());
        }
        try{
            return Number(std::stol(input.substr(0,slash_pos)),
                            static_cast<unsigned>(std::stoi(input.substr(slash_pos+1))));
        }
        catch (std::exception& e){
            throw RuntimeException(e.what(), var_name->get_line_no());
        }
    }*/
}

}
