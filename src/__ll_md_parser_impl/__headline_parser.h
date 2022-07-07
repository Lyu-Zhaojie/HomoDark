#include <array>
#if __cplusplus >= 201703L
#ifndef __HEADLINE_PARSER_H
#define __HEADLINE_PARSER_H 1
#include "__block_parser.h"
#include "__md_config.h"
#include <regex>
#include <functional>

namespace ll_markdown
{
    class HeadlineParser : public BlockParser
    {
    public:
        HeadlineParser(std::function<void(string_t &)> parse_line_callback,
                       std::function<std::shared_ptr<BlockParser>(const string_t &)> block_parser_for_line_callback)
            : BlockParser(parse_line_callback, block_parser_for_line_callback) {}

        static bool is_start_line(const string_t &line)
        {
            static regex_t re{u8"^(?:#){1,6} (.*)"};
            return std::regex_match(line, re);
        }

        bool is_finished() const override { return true; }

    protected:
        bool is_inline_block_allowed() const override { return false; }
        bool is_line_parser_allowed() const override { return false; }
        void parse_block(string_t &line) override
        {
            static std::array<regex_t, 6> regexes{
                regex_t{u8"^# (.*)"},
                regex_t{u8"^(?:#){2} (.*)"},
                regex_t{u8"^(?:#){3} (.*)"},
                regex_t{u8"^(?:#){4} (.*)"},
                regex_t{u8"^(?:#){5} (.*)"},
                regex_t{u8"^(?:#){6} (.*)"}};
            static std::array<string_t, 6> replacements{
                u8"<h1>$1</h1>",
                u8"<h2>$1</h2>",
                u8"<h3>$1</h3>",
                u8"<h4>$1</h4>",
                u8"<h5>$1</h5>",
                u8"<h6>$1</h6>"};
            for (int i{0}; i < 6; i++)
                line = std::regex_replace(line, regexes[i], replacements[i]);
        }
    };
}
#endif // __HEADLINE_PARSER_H
#else
#error Use a compiler that supports C++ 17
#endif // C++ 17
