#if __cplusplus >= 201703L
#ifndef __HIGHLIGHT_PARSER_H
#define __HIGHLIGHT_PARSER_H 1
#include "__md_config.h"
#include <regex>

namespace ll_markdown
{
    /**
     * HighlightParser
     *
     * @class
     * @brief 解析行内高亮
     */
    class HighlightParser
    {
    public:
        void parse(string_t &line)
        {
            // __________s____________(?!.*`.*|.*<code>.*)==(?!.*`.*|.*<\/code>.*)([^==]*)==(?!.*`.*|.*<\/code>.*)
            static regex_t re{u8R"((?!.*`.*|.*<code>.*)==(?!.*`.*|.*<\/code>.*)([^==]*)==(?!.*`.*|.*<\/code>.*))"};
            static string_t replacement{u8R"(<mark>$1</mark>)"};
            line = std::regex_replace(line, re, replacement);
        }
    };
}
#endif // __HIGHLIGHT_PARSER_H
#else
#error Use a compiler that supports C++ 17.
#endif // C++ 17
