#if __cplusplus >= 201703L
#ifndef __ORDERED_LIST_PARSER_H
#define __ORDERED_LIST_PARSER_H 1
#include "__block_parser.h"
#include "__md_config.h"
#include <functional>
#include <regex>


namespace ll_markdown
{
    class OrderedListParser : public BlockParser
    {
    public:
        OrderedListParser(std::function<void(string_t &)> parse_line_callback,
                          std::function<std::shared_ptr<BlockParser>(const string_t &)> block_parser_for_line_callback)
            : BlockParser(parse_line_callback, block_parser_for_line_callback) {}

        static bool is_start_line(const string_t &line)
        {
            static regex_t re{u8R"(^1\. .*)"};
            return std::regex_match(line, re);
        }

        bool is_finished() const override { return m_is_finished; }

    protected:
        bool is_inline_block_allowed() const override { return true; }
        bool is_line_parser_allowed() const override { return true; }

        void parse_block(string_t &line) override
        {
            bool is_start_of_new_item_v{is_start_of_new_item(line)};
            int indent{get_indent(line)};

            static regex_t ordered_item_regex{u8R"(^[1-9]+[0-9]*\. )"};
            static regex_t unordered_item_regex{u8R"(^[\*\-\+] )"};
            line = std::regex_replace(line, ordered_item_regex, u8"");
            line = std::regex_replace(line, unordered_item_regex, u8"");
            if (!m_is_started)
            {
                line = u8"<ol><li>" + line;
                m_is_started = true;
                return;
            }
            if (indent >= 2)
            {
                line = line.substr(2);
                return;
            }
            if (line.empty() ||
                line.find(u8"</li><li>") != string_t::npos ||
                line.find(u8"</li></ol>") != string_t::npos ||
                line.find(u8"</li></ul>") != string_t::npos)
            {
                line = u8"</li></ol>" + line;
                m_is_finished = true;
                return;
            }
            if (is_start_of_new_item_v)
                line = u8"</li><li>" + line;
        }

    private:
        bool m_is_started{false}, m_is_finished{false};

        bool is_start_of_new_item(const string_t &line) const
        {
            static regex_t re{u8R"(^(?:[1-9]+[0-9]*\. |[\*\-\+] ).*)"};
            return std::regex_match(line, re);
        }
    };
}
#endif // __ORDERED_LIST_PARSER_H
#else
#error Use a compiler that supports C++ 17.
#endif // C++ 17
