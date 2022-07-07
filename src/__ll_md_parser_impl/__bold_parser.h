#if __cplusplus >= 201703L
#ifndef __BOLD_PARSER_H
#define __BOLD_PARSER_H 1
#include "__md_config.h"
#include <regex>

namespace ll_markdown
{
    /**
     * BoldParser
     *
     * @class
     * @brief 解析行内粗体
     */
    class BoldParser
    {
    public:
        void parse(string_t &line)
        {
            // Edition1: ______________________(?!.*`.*|.*<code>.*)\*\*(?!.*`.*|.*<\/code>.*)([^\*\*]*)\*\*(?!.*`.*|.*<\/code>.*)
            // Edition2: (?!.*`.*|.*<code>.*)\*\*(.*?)\*\*(?!.*`.*|.*<\/code>.*)
            static regex_t re{u8R"((?!.*`.*|.*<code>.*)\*\*(.*?)\*\*(?!.*`.*|.*<\/code>.*))"};
            static string_t replacement{u8R"(<b>$1</b>)"};
            line = std::regex_replace(line, re, replacement);
        }
    };
}
#endif // __BOLD_PARSER_H
#else
#error Use a compiler that supports C++ 17.
#endif // C++ 17
