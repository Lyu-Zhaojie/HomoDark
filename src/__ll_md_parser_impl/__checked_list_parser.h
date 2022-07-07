#if __cplusplus >= 201703L
#ifndef __CHECKED_LIST_PARSER_H
#define __CHECKED_LIST_PARSER_H 1
#include "__block_parser.h"
#include "__md_config.h"
#include <functional>
#include <regex>

namespace ll_markdown
{
    class CheckedListParser : public BlockParser
    {
    public:
        CheckedListParser(std::function<void(string_t &)> parse_line_callback,
                          std::function<std::shared_ptr<BlockParser>(const string_t &)> block_parser_for_line_callback)
            : BlockParser(parse_line_callback, block_parser_for_line_callback) {}

        static bool is_start_line(const string_t &line)
        {
            static regex_t re{u8R"(^- \[[x| ]\] .*)"};
            return std::regex_match(line, re);
        }

        bool is_finished() const override { return m_is_finished; }

    protected:
        bool is_inline_block_allowed() const override { return true; }
        bool is_line_parser_allowed() const override { return true; }

        void parse_block(string_t &line) override
        {
            bool is_start_of_new_item_v{is_start_line(line)};
            int indent{get_indent(line)};

            static regex_t line_regex{u8"^(- )"};
            line = std::regex_replace(line, line_regex, u8"");

            static regex_t empty_box_regex{u8R"(\[ \])"};
            static string_t empty_box_replacement = u8R"(<input type="checkbox"/>)";
            line = std::regex_replace(line, empty_box_regex, empty_box_replacement);

            static regex_t checked_box_regex{u8R"(^\[x\])"};
            static string_t checked_box_replacement{u8R"(<input type="checkbox" checked="checked"/>)"};
            line = std::regex_replace(line, checked_box_regex, checked_box_replacement);

            if (m_is_started)
            {
                line = u8R"(<ul class="checklist"><li><label>)" + line;
                m_is_started = true;
                return;
            }

            if (indent >= 2)
            {
                line = line.substr(2);
                return;
            }

            if (line.empty() ||
                line.find(u8"</label></li><li><label>") != string_t::npos ||
                line.find(u8"</label></li></ul>") != string_t::npos)
            {
                line = "</label></li></ul>" + line;
                m_is_finished = true;
                return;
            }

            if (is_start_of_new_item_v)
                line = "</label></li><li><label>" + line;
        }

    private:
        bool m_is_started{false}, m_is_finished{false};
    };
}
#endif
#endif