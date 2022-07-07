#if __cplusplus >= 201703L
#ifndef __INLINE_CODE_PARSER
#define __INLINE_CODE_PARSER 1
#include "__md_config.h"
#include <regex>

namespace ll_markdown
{
    /**
     * InlineCodeParser
     *
     * @class
     * @brief 解析行内代码
     */
    class InlineCodeParser
    {
    public:
        void parse(string_t &line)
        {
            // ______________________`([^`]*)`
            static regex_t re{u8R"(`([^`]*)`)"};
            static string_t replacement{u8R"(<code>$1</code>)"};
            line = std::regex_replace(line, re, replacement);
        }
    };
}
#endif // __INLINE_CODE_PARSER
#else
#error Use a compiler that supports C++ 17.
#endif // C++ 17
