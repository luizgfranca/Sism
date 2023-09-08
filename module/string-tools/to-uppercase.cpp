#include "to-uppercase.h"



std::string string_tools::to_uppercase(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), 
        [](unsigned char c){ return std::toupper(c); }
    );
    return s;
}