#pragma once

#include "encoding.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <cstdint>

namespace Celeste {
    class MapBin {
        public:
        std::string checksum;
        std::string package;
        std::vector<std::uint8_t> data;
        
        MapBin(std::istream& fh) {
            checksum = readString(fh);
            
            if (checksum != "CELESTE MAP") {
                throw "Invalid checksum";
            }
            
            package = readString(fh);
            
            auto byte = fh.get();
            while (byte != std::char_traits<decltype(byte)>::eof()) {
                data.push_back(byte);
                byte = fh.get();
            }
        }
        
        std::vector<std::uint8_t> encode() {
            auto res = makeString(checksum);
            
            auto packageBytes = makeString(package);
            
            res.insert(res.end(), packageBytes.begin(), packageBytes.end());
            
            res.insert(res.end(), data.begin(), data.end());
            
            return res;
        }
    };
}