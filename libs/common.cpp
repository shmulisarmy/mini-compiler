#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <span>
#include "unordered_set"
#include "unordered_map"



using std::map;
using std::string;
using std::vector;
using std::unordered_set;
using std::unordered_map;
using std::cin;
using std::cout;
using std::endl;


#define uint unsigned int

// Shortened function definition
#define fn void inline

// Simple loop macro
#define Loop(amount, var_name) for (size_t var_name = 0; var_name < (amount); ++var_name)

// Debugging: Print variable name and value
#define debug(x) std::cerr << "[DEBUG]:\n" << #x << " = " << (x) << " (line " << __FILE__ << ":" << __LINE__ << ")\n";

// Debugging: Variadic debug (for multiple variables)
#define dbg_vars(...) debug_out(#__VA_ARGS__, __VA_ARGS__)

// Likely/unlikely for branch prediction hints
#if defined(__GNUC__) || defined(__clang__)
#define likely(x)   __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)
#else
#define likely(x)   (x)
#define unlikely(x) (x)
#endif

// Variadic debug function (helper for dbg_vars)
inline void debug_out(const char* name) {
    std::cerr << std::endl;
}

template<typename T, typename... Args>
inline void debug_out(const char* names, T&& value, Args&&... args) {
    const char* comma = strchr(names, ',');
    std::cerr.write(names, comma - names) << " = " << value << " | ";
    debug_out(comma + 1, std::forward<Args>(args)...);
}

#define assert(condition, message) \
    if (!(condition)) { \
        std::cerr << "Assertion failed: " << message << "\n" \
                  << "Condition: " << #condition << "\n" \
                  << __FILE__ << ":" << __LINE__ << "\n" << std::endl; \
        std::abort(); \
    }
#define FILELINE std::string(" in ") + __FILE__ + ":" + std::to_string(__LINE__)