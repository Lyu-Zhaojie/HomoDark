#if __cplusplus >= 201703L
#ifndef __MD_CONFIG_H
#define __MD_CONFIG_H 1
#include <regex>
#include <string>
using char_t = char;
using string_t = std::basic_string<char_t>;
using regex_t = std::basic_regex<char_t>;
#endif // __MD_CONFIG_H
#else
#error Use a compiler that supports C++ 17.
#endif // C++ 17
