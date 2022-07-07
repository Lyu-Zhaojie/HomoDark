#if __cplusplus >= 201703L
#ifndef __DELETE_LINE_PARSER_H
#define __DELETE_LINE_PARSER_H 1
#include "__md_config.h"
#include <regex>

namespace ll_markdown
{
    /**
     * DeleteLineParser
     *
     * @class
     * @brief 解析删除线
     */
    class DeleteLineParser
    {
    public:
        void parse(string_t &line)
        {
            static regex_t re{u8R"((?!.*`.*|.*<code>.*)\~\~(?!.*`.*|.*<\/code>.*)([^\~]*)\~\~(?!.*`.*|.*<\/code>.*))"};
            // ______________________\[([^\]]*)\]\(([^\]]*)\)
            static string_t replacement{u8R"(<del>$1</del>)"};
            line = std::regex_replace(line, re, replacement);
        }
    };
}
#endif // __DELETE_LINE_PARSER_H
#else
#error Use a compiler that supports C++ 17.
#endif // C++ 17
