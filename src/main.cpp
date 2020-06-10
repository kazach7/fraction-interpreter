#include "../include/modules/Source.h"
#include "../include/modules/Scanner.h"
#include "../include/modules/Parser.h"
#include "../include/Token.h"
#include "../include/program-tree/program-tree-includes.h"
#include "../include/environment/environment-includes.h"
#include "../include/exceptions/SourceException.h"
#include "../include/exceptions/ScannerException.h"
#include "../include/exceptions/ParserException.h"
#include "../include/exceptions/RuntimeException.h"
#include <iostream>
#include <fstream>
#include <optional>
using namespace kazachTKOM;
using TokenType = Token::TOKEN_TYPE;

void print_separator()
{
    std::cout << std::endl <<
        "=======================================================" << std::endl;
}

int main(int argc, char* argv[]) 
{
    if (argc < 2 || argc > 3 || argc == 3 && strcmp(argv[2], "-i") != 0 && strcmp(argv[2],"--integer") != 0) {
        std::cerr << "usage: interpreter_tkom path_to_script [-i | --integral]" << std::endl << std::endl
            << "path_to_script\t Path to file with a script" << std::endl
            << "--integer\t Fractions will be displayed with separated integral part" << std::endl;
        return 1;
    }

    std::ifstream stream;
    stream.open(argv[1]);
    if (stream.fail()) {
        std::cerr << "Could not open the file." << std::endl;
        return 1;
    }

    if (argc == 3) {
        StdoutPrint::display_integral_part = true;
    }

    try {
        Source source(stream);
        Scanner scanner(source,
            { {"Start", TokenType::T_START_KW},   {"Funkcja", TokenType::T_FUNKCJA_KW},
              {"Wypisz", TokenType::T_WYPISZ_KW}, {"Pobierz", TokenType::T_POBIERZ_KW},
              {"Dopoki", TokenType::T_DOPOKI_KW}, {"Koniec", TokenType::T_KONIEC_KW},
              {"Jezeli", TokenType::T_JEZELI_KW}, {"Przeciwnie", TokenType::T_PRZECIWNIE_KW},
              {"Zwroc", TokenType::T_ZWROC_KW},   {"KoniecProgramu", TokenType::T_KONIECPROG_KW}
            });

        Parser parser(scanner);
        auto program = parser.parse_program();
        std::cout << "File successfully parsed." << std::endl;

        Environment environment;

        bool do_execute = true;
        while (do_execute) {
            std::cout << "Starting the execution. You will see the results below.";
            print_separator();

            std::optional<std::string> status;
            try {
                Environment environment;
                auto status = program->execute(environment);

                print_separator();
                if (status) std::cout << "Program returned value: " << *status;
                else std::cout << "Program did not return any value.";
            }
            catch (RuntimeException& e) {
                print_separator();
                std::cout << e.what() << std::endl;
            }

            char dec;
            std::cout << std::endl << "Execute again? y=yes ";
            std::cin >> dec;
            if (dec != 'y' && dec != 'Y') do_execute = false;
            else std::cout << std::endl;
        }
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
  
    return 0;
}