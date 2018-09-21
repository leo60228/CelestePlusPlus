#pragma once

#include <string>
#include <algorithm>
#include <iostream>
#include <map>
#include <cctype>

namespace Celeste {
    void eatBytes(std::istream& fh, std::string bytes) {
        while (bytes.find(fh.peek()) != std::string::npos) fh.ignore();
    }
    
    bool myIsSpace(char byte) {
        return std::isspace(byte) || byte == '\r' || byte == 0xfe || byte == 0xff || !std::isprint(byte);
    }
    
    std::string readLine(std::istream& fh) {
        std::string res;
        
        while (fh.peek() != '\n' && !fh.eof()) {
            res.push_back(fh.get());
        }
        
        fh.ignore();
        
        return res;
    }
    
    class Dialog : public std::map<std::string, std::string> {
        bool processEntry(std::istream& fh) {
            auto firstChar = fh.peek();
            
            if (fh.eof()) return false;
            
            if (firstChar == '#') {
                readLine(fh);
                return true;
            }
            
            while (std::isspace(fh.peek())) {
                fh.ignore();
            }
            
            firstChar = fh.peek();
            while (firstChar == '#') {
                readLine(fh);
                firstChar = fh.peek();
            }
            
            while (std::isspace(fh.peek())) {
                fh.ignore();
            }
            
            while (firstChar == '#') {
                readLine(fh);
                firstChar = fh.peek();
            }
            
            std::string name;
            std::string value;
            int tabCount = 0;
            bool newLine = false;
            
            while (true) {
                if (!newLine) {
                    auto byte = fh.get();
                    
                    while (byte == '#') {
                        readLine(fh);
                        byte = fh.get();
                    }
                    
                    auto p = fh.peek();
                    
                    name.push_back(byte);
                    
                    if (p == '=') {
                        fh.ignore();
                        break;
                    }
                    
                    if (byte == std::char_traits<decltype(byte)>::eof()) return false;
                }
            }
            
            name.erase(remove_if(name.begin(), name.end(), myIsSpace), name.end());
            
            newLine = false;
            tabCount = 0;
            
            while (std::isspace(fh.peek())) {
                fh.ignore();
            }
            
            while (true) {
                bool ignore = true;
                auto byte = fh.peek();
                
                if (newLine) {
                    if (byte == '\t') {
                        tabCount++;
                    } else if (byte == '#') {
                        readLine(fh);
                    } else {
                        break;
                    }
                    
                    if (tabCount >= 2) {
                        tabCount = 0;
                        newLine = false;
                    }
                    
                } else {
                    if (byte == '\n') newLine = true;
                    
                    if (fh.peek() == std::char_traits<decltype(byte)>::eof()) break;
                    
                    if (std::isprint(byte) || byte == '\n') value.push_back(byte);
                }
                
                if (ignore) fh.ignore();
            }
            
            if (value[value.length() - 1] == '\n') {
                value.pop_back();
            }
            
            (*this)[name] = value;
            
            return !fh.eof();
        }
        
        public:
        Dialog(std::istream& fh) {
            while (processEntry(fh)) {}
        }
        
        std::string encode() {
            std::string res;
            
            for (auto e : *this) {
                res += "\t";
                res += e.first;
                res += "=\n\t\t";
                
                for (auto byte : e.second) {
                    if (byte == '\n') {
                        res += "\n\t\t";
                    } else {
                        res.push_back(byte);
                    }
                }
                
                res += "\n";
            }
            
            return res;
        }
    };
}