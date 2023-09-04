#include "../Headers/urlDecoder.h"

std::string urlDecode(const std::string& src) {
    std::string ret;
    char ch;
    for (size_t i = 0; i < src.length(); i++) {
        if (src[i] == '%') {
            if (i + 2 < src.length() && isxdigit(src[i + 1]) && isxdigit(src[i + 2])) {
                std::string hex = src.substr(i + 1, 2);
                unsigned int value;
                std::istringstream hexstream(hex);
                hexstream >> std::hex >> value;
                ret += static_cast<char>(value);
                i += 2;
            }
        }
        else if (src[i] == '+') {
            ret += ' ';
        }
        else {
            ret += src[i];
        }
    }
    return ret;
}