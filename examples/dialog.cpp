#include <iostream>
#include <fstream>

#include "celeste/dialog.hpp"

int main() {
    std::ifstream dialogFile("dialog.txt");
    std::ofstream newDialogFile("new-dialog.txt");
    
    Celeste::Dialog dialog(dialogFile);
    
    for (auto dialogLine : dialog) {
        std::cerr << "name is \"" << dialogLine.first << "\"" << std::endl;
        std::cerr << "contents:" << std::endl;
        std::cerr << dialogLine.second;
        std::cerr << std::endl << std::endl;
    }
    
    std::cerr << "reencoded:" << std::endl;
    std::cout << dialog.encode();
    newDialogFile << dialog.encode();
    
    newDialogFile.close();
    
    std::ifstream newDialogFileIn("new-dialog.txt");
    
    Celeste::Dialog newDialog(newDialogFileIn);
    
    std::cerr << std::endl << "new dialog is " << (newDialog == dialog ? "correct" : "incorrect") << std::endl;
    
    if (newDialog != dialog) {
        for (auto dialogLine : newDialog) {
            std::cerr << dialogLine.first << " is " << (dialogLine.second == dialog[dialogLine.first] ? "correct" : "incorrect") << std::endl;
        }
    }
    
    return 0;
}