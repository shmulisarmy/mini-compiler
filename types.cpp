#include "libs/common.cpp"
#include <unordered_set>
#include <string>

const std::unordered_set<std::string> built_in_types = {
    "if", "else", "while", "for", "do", "break", "continue", "return",
    "switch", "case", "default", "try", "catch", "finally", "throw",
    "synchronized", "native", "static"
};

std::unordered_set<std::string> user_defined_types;
