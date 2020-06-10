#include "../../include/modules/StdIOManager.h"
#include <iostream>
#include <sstream>
namespace kazachTKOM{

void StdIOManager::print_on_stdout(const std::string& output)
{
    std::cout << output;
}

std::string StdIOManager::get_from_stdin()
{
    std::cin.clear();
    if (std::cin.peek() == '\n') { // Remove trailing '\n' after possible reading with cin by the process.
        std::cin.ignore(1, '\n');
    }
    std::string input;
    std::getline(std::cin, input);

    return input;
}

}
