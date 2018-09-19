#pragma once

#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <cstdint>

namespace Celeste {
    int getVarLength(std::istream& fh) {
        int res = 0;
        int count = 0;
        while (true) {
            std::uint8_t byte = fh.get();
            res += (byte & 127) << (count * 7);
            ++count;
            if ((byte >> 7) == 0) {
                return res;
            }
        }
    }

    std::vector<std::uint8_t> makeVarLength(int n) {
        std::vector<std::uint8_t> res;
        while (n > 127) {
            res.push_back(n & 127 | 0b10000000);
        }
        res.push_back(n);
        return res;
    }

    std::string readString(std::istream& fh) {
        int length = getVarLength(fh);
        std::string res = "";
        
        for (int i = 0; i < length; i++) {
            res.push_back(fh.get());
        }
        
        return res;
    }

    std::vector<std::uint8_t> makeString(std::string str) {
        std::vector<std::uint8_t> res = makeVarLength(str.length());
        std::copy(str.begin(), str.end(), std::back_inserter(res));
        return res;
    }
}