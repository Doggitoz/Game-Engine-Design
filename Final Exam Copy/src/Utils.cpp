#pragma once

#include <string>
#include <iomanip>

class Utils {
    public:
        static std::string Truncate(float f);
};

std::string Utils::Truncate(float f) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << f;
    std::string str = ss.str();
    // Ensure that there is a decimal point somewhere (there should be)
    if(str.find('.') != std::string::npos)
    {
        // Remove trailing zeroes
        str = str.substr(0, str.find_last_not_of('0')+1);
        // If the decimal point is now the last character, remove that as well
        if(str.find('.') == str.size()-1)
        {
            str = str.substr(0, str.size()-1);
        }
    }
    return str;
}