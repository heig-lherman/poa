#include "utils.hpp"

std::pair<std::string, std::string> utils::split(const std::string& str,
                                                 char delimiter) {
    std::size_t pos = str.find(delimiter);
    if (pos == std::string::npos) {
        return {str, ""};
    }

    return {str.substr(0, pos), str.substr(pos + 1)};
}
