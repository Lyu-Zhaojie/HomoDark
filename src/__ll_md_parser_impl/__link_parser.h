#if __cplusplus >= 201703L
#ifndef __LINK_PARSER_H
#define __LINK_PARSER_H 1
#include "__md_config.h"
#include <regex>

namespace ll_markdown
{
    /**
     * LinkParser
     *
     * 在 `ImageParser` 后使用
     *
     * @class
     * @brief 解析超链接
     */
    class LinkParser
    {
    public:
        void parse(string_t &line)
        {
            // ______________________\[([^\]]*)\]\(([^\]]*)\)
            static regex_t re{u8R"(\[([^\]]*)\]\(([^\]]*)\))"};
            static string_t replacement{u8R"(<a href="$2">$1</a>)"};
            line = std::regex_replace(line, re, replacement);
        }
    };
}
#endif // __LINK_PARSER_H
#else
#error Use a compiler that supports C++ 17.
#endif // C++ 17
