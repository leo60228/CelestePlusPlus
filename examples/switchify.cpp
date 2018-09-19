//#include <filesystem>
#include <experimental/filesystem>
#include <string>
#include <fstream>
#include <iostream>

#include "celeste/mapbin.hpp"

//namespace fs = std::filesystem;
namespace fs = std::experimental::filesystem;

int main(int argc, char* argv[]) {
    std::string inPath = argv[1];
    std::string outPath = argv[2];
    
    for (auto& mapBin : fs::directory_iterator(inPath)) {
        auto correctPackage = mapBin.path().stem();
        
        std::ifstream mapBinStream(mapBin.path());
        
        Celeste::MapBin map(mapBinStream);
        
        std::cout << "current package: \"" << map.package << "\"" << std::endl;
        std::cout << "correct package: " << correctPackage << std::endl;
        map.package = correctPackage;
        std::cout << "package fixed" << std::endl;
        
        auto fixedPath = outPath / mapBin.path().filename();
        
        std::ofstream newMapBin(fixedPath);
        
        for (auto e : map.encode()) {
            newMapBin.put(e);
        }
        
        std::cout << "map saved to: " << fixedPath << std::endl;
    }
    
    return 0;
}