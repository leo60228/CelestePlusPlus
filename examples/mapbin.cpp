#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <cstdint>
#include "celeste/mapbin.hpp"

int main() {
    std::ifstream mapBin("empty.bin");
    std::ofstream newMapBin("7-Summit.bin");
    
    Celeste::MapBin map(mapBin);
    
    std::cout << map.checksum << std::endl;
    std::cout << map.package << std::endl;
    
    map.package = "7-Summit";
        
    for (auto e : map.encode()) {
        newMapBin.put(e);
    }
    
    return 0;
}
