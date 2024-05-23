#pragma once

#include <string>

namespace utils {

std::pair<std::string, std::string> split(const std::string& str,
                                          char delimiter);
}