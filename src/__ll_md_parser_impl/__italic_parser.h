#if __cplusplus >= 201703L
#ifndef __ITALIC_PARSER_H
#define __ITALIC_PARSER_H 1
#include "__md_config.h"
#include <regex>

namespace ll_markdown
{
    /**
     * ItalicParser
     *
     * @class
     * @brief 解析行内斜体
     */
    class ItalicParser
    {
    public:
        void parse(string_t &line)
        {
            // ______________________(?!.*`.*|.*<code>.*)\*(?!.*`.*|.*<\/code>.*)([^\*]*)\*(?!.*`.*|.*<\/code>.*)
            static regex_t re{u8R"((?!.*`.*|.*<code>.*)\*(?!.*`.*|.*<\/code>.*)([^\*]*)\*(?!.*`.*|.*<\/code>.*))"};
            static string_t replacement{u8R"(<i>$1</i>)"};
            line = std::regex_replace(line, re, replacement);
        }
    };
}
#endif // __ITALIC_PARSER_H
#else
#error Use a compiler that supports C++ 17.
#endif // C++ 17
