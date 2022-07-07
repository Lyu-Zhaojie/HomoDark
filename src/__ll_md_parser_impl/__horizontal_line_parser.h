#if __cplusplus >= 201703L
#ifndef __HORIZONTAL_LINE_PARSER_H
#define __HORIZONTAL_LINE_PARSER_H 1
#include "__block_parser.h"
#include "__md_config.h"
#include <functional>
#include <regex>

namespace ll_markdown
{
    class HorizontalLineParser : public BlockParser
    {
    public:
        HorizontalLineParser(std::function<void(string_t &)> parse_line_callback,
                             std::function<std::shared_ptr<BlockParser>(const string_t &)> block_parser_for_line_callback)
            : BlockParser(parse_line_callback, block_parser_for_line_callback) {}

        static bool is_start_line(const string_t &line)
        {
            static regex_t re{u8R"(^\*\*\*$)"};
            return std::regex_match(line, re);
        }

        bool is_finished() const override { return true; }

    protected:
        bool is_inline_block_allowed() const override { return false; }
        bool is_line_parser_allowed() const override { return false; }

        void parse_block(string_t &line) override
        {
            static regex_t line_regex{u8R"(^\*\*\*$)"};
            static string_t replacement = u8"<hr/>";
            line = std::regex_replace(line, line_regex, replacement);
        }
    };
}
#endif // __HORIZONTAL_LINE_PARSER_H
#else
#error Use a compiler that supports C++ 20.
#endif // C++ 201703L
