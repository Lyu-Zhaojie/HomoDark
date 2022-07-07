#if __cplusplus >= 201703L
#ifndef __BREAK_LINE_PARSER_H
#define __BREAK_LINE_PARSER_H 1
#include "__md_config.h"
#include <regex>

namespace ll_markdown
{
    /**
     * BreakLineParser
     *
     * @class
     * @brief 解析换行符
     */
    class BreakLineParser
    {
    public:
        void parse(string_t &line)
        {
            // ______________________crlf / cr
            static regex_t re{u8R"((\r\n|\r))"};
            static string_t replacement{u8R"(</br>)"};
            line = std::regex_replace(line, re, replacement);
        }
    };
}
#endif // __BREAK_LINE_PARSER_H
#else
#error Use a compiler that supports C++ 17.
#endif // C++ 17
