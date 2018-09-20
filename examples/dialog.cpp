#include <iostream>
#include <fstream>

#include "celeste/dialog.hpp"

int main() {
    std::ifstream dialogFile("dialog.txt");
    
    Celeste::Dialog dialog(dialogFile);
    
    for (auto dialogLine : dialog) {
        std::cout << "name is \"" << dialogLine.first << "\"" << std::endl;
        std::cout << "contents:" << std::endl;
        std::cout << dialogLine.second;
        std::cout << std::endl << std::endl;
    }
    
    return 0;
}