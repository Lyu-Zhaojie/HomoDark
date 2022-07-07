#if __cplusplus >= 201703L
#ifndef __IMAGE_PARSER
#define __IMAGE_PARSER 1
#include "__md_config.h"
#include <regex>

namespace ll_markdown
{
    /**
     * ImageParser
     *
     * 在 `LinkParser` 前使用
     *
     * @class
     * @brief 解析图片
     */
    class ImageParser
    {
    public:
        void parse(string_t &line)
        {
            // ______________________\!\[([^\]]*)\]\(([^\]]*)\)
            static regex_t re{u8R"(\!\[([^\]]*)\]\(([^\]]*)\))"};
            static string_t replacement{u8R"(<img src="$2" alt="$1"/>)"};
            line = std::regex_replace(line, re, replacement);
        }
    };
}
#endif // __IMAGE_PARSER
#else
#error Use a compiler that supports C++ 17.
#endif // C++ 17
