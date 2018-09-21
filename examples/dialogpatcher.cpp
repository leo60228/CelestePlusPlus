#include <iostream>
#include <fstream>

#include "celeste/dialog.hpp"

int main() {
    std::ifstream dialogFile("dialog.txt");
    std::ifstream patchFile("dialog-patch.txt");
    std::ofstream newDialogFile("patched-dialog.txt");
    
    Celeste::Dialog dialog(dialogFile);
    Celeste::Dialog patch(patchFile);
    
    for (auto patchLine : patch) {
        dialog[patchLine.first] = patchLine.second;
    }
    
    std::cerr << "patched:" << std::endl;
    std::cout << dialog.encode();
    newDialogFile << dialog.encode();
    
    newDialogFile.close();
    
    return 0;
}