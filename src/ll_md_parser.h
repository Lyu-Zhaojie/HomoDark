#if __cplusplus >= 201703L
#ifndef LL_MD_PARSER
#define LL_MD_PARSER 1
#include "__ll_md_parser_impl/__md_config.h"
#include <istream>
#include <string>

// Line parsers.
#include "__ll_md_parser_impl/__bold_parser.h"
#include "__ll_md_parser_impl/__break_line_parser.h"
#include "__ll_md_parser_impl/__delete_line_parser.h"
#include "__ll_md_parser_impl/__highlight_parser.h"
#include "__ll_md_parser_impl/__image_parser.h"
#include "__ll_md_parser_impl/__inline_code_parser.h"
#include "__ll_md_parser_impl/__italic_parser.h"
#include "__ll_md_parser_impl/__link_parser.h"

// Block parsers.
#include "__ll_md_parser_impl/__block_parser.h"
#include "__ll_md_parser_impl/__checked_list_parser.h"
#include "__ll_md_parser_impl/__code_block_parser.h"
#include "__ll_md_parser_impl/__headline_parser.h"
#include "__ll_md_parser_impl/__horizontal_line_parser.h"
#include "__ll_md_parser_impl/__ordered_list_parser.h"
#include "__ll_md_parser_impl/__para_parser.h"
#include "__ll_md_parser_impl/__quotation_parser.h"
#include "__ll_md_parser_impl/__unordered_list_parser.h"

#include <memory>

namespace ll_markdown
{
    class Parser
    {
    public:
        /**
         * @brief parse Markdown to HTML.
         *
         * @param markdown
         * @return string_t HTML body.
         */
        string_t parse(std::basic_istream<char_t> &markdown) const
        {
            string_t result;
            std::shared_ptr<BlockParser> current_block_parser{nullptr};
            string_t line;
            while (std::getline(markdown, line, u8'\n'))
            {
                if (!current_block_parser)
                    current_block_parser = get_block_parser_for_line(line);
                if (current_block_parser)
                {
                    current_block_parser->add_line(line);
                    if (current_block_parser->is_finished())
                    {
                        result += current_block_parser->get_result().str();
                        current_block_parser = nullptr;
                    }
                }
            }

            // Make sure all parsers are finished.
            if (current_block_parser)
            {
                string_t empty_line;
                current_block_parser->add_line(empty_line);
                if (current_block_parser->is_finished())
                {
                    result += current_block_parser->get_result().str();
                    current_block_parser = nullptr;
                }
            }
            return result;
        }

    private:
        std::shared_ptr<BoldParser> bold_parser{std::make_shared<BoldParser>()};
        std::shared_ptr<ImageParser> image_parser{std::make_shared<ImageParser>()};
        std::shared_ptr<ItalicParser> italic_parser{std::make_shared<ItalicParser>()};
        std::shared_ptr<DeleteLineParser> delete_line_parser{std::make_shared<DeleteLineParser>()};
        std::shared_ptr<LinkParser> link_parser{std::make_shared<LinkParser>()};
        std::shared_ptr<BreakLineParser> break_line_parser{std::make_shared<BreakLineParser>()};
        std::shared_ptr<InlineCodeParser> inline_code_parser{std::make_shared<InlineCodeParser>()};
        std::shared_ptr<HighlightParser> highlight_parser{std::make_shared<HighlightParser>()};
        void parser_line(string_t &line) const
        {
            image_parser->parse(line);
            link_parser->parse(line);
            bold_parser->parse(line);
            highlight_parser->parse(line);
            delete_line_parser->parse(line);
            inline_code_parser->parse(line);
            italic_parser->parse(line);
            break_line_parser->parse(line);
        }

        /**
         * @brief Get a smart pointer of `BlockParser` for a line.
         *
         * @param line
         * @return std::shared_ptr<BlockParser>
         */
        auto get_block_parser_for_line(const string_t &line) const -> std::shared_ptr<BlockParser>
        {
            std::shared_ptr<BlockParser> parser{nullptr};

            if (CodeBlockParser::is_start_line(line))
                parser = std::make_shared<CodeBlockParser>(nullptr, nullptr);

            else if (HeadlineParser::is_start_line(line))
                parser = std::make_shared<HeadlineParser>(nullptr, nullptr);

            else if (HorizontalLineParser::is_start_line(line))
                parser = std::make_shared<HorizontalLineParser>(nullptr, nullptr);

            else if (QuotationParser::is_start_line(line))
                // parser = std::make_shared<QuotationParser>(
                //     [this](string_t &line)
                //     { this->parser_line(line); },

                //     [this](const string_t &line)
                //     { return this->get_block_parser_for_line(line); });
                parser = create_quotation_parser();

            else if (CheckedListParser::is_start_line(line))
                parser = create_checked_list_parser();

            else if (OrderedListParser::is_start_line(line))
                parser = create_ordered_list_parser();

            else if (UnorderedListParser::is_start_line(line))
                parser = create_unordered_list_parser();

            else if (ParaParser::is_start_line(line))
                parser = std::make_shared<ParaParser>(
                    [this](string_t &line)
                    { this->parser_line(line); },

                    nullptr);

            return parser;
        }

        auto create_quotation_parser() const -> std::shared_ptr<QuotationParser>
        {
            return std::make_shared<QuotationParser>(
                [this](string_t &line)
                { this->parser_line(line); },

                [this](const string_t &line)
                {
                    std::shared_ptr<BlockParser> parser{nullptr};
                    if (QuotationParser::is_start_line(line))
                        parser = this->create_quotation_parser();
                    return parser;
                }
            );
        }

        /**
         * @brief Create a smart pointer of `CheckedListParser`.
         *
         * @return std::shared_ptr<BlockParser>
         */
        auto create_checked_list_parser() const -> std::shared_ptr<BlockParser>
        {
            return std::make_shared<CheckedListParser>(
                [this](string_t &line)
                { this->parser_line(line); },

                [this](const string_t &line)
                {
                    std::shared_ptr<BlockParser> parser{nullptr};
                    if (CheckedListParser::is_start_line(line))
                        parser = this->create_checked_list_parser();
                    return parser;
                });
        }

        /**
         * @brief Create a smart pointer of `OrderedListParser`.
         *
         * @return std::shared_ptr<BlockParser>
         */
        auto create_ordered_list_parser() const -> std::shared_ptr<BlockParser>
        {
            return std::make_shared<OrderedListParser>(
                [this](string_t &line)
                { this->parser_line(line); },

                [this](const string_t &line)
                {
                    std::shared_ptr<BlockParser> parser{nullptr};
                    if (OrderedListParser::is_start_line(line))
                        parser = this->create_ordered_list_parser();
                    else if (UnorderedListParser::is_start_line(line))
                        parser = this->create_unordered_list_parser();
                    return parser;
                });
        }

        /**
         * @brief Create a smart pointer of `UnorderedListParser`.
         *
         * @return std::shared_ptr<BlockParser>
         */
        auto create_unordered_list_parser() const -> std::shared_ptr<BlockParser>
        {
            return std::make_shared<UnorderedListParser>(
                [this](string_t &line)
                { this->parser_line(line); },

                [this](const string_t &line)
                {
                    std::shared_ptr<BlockParser> parser{nullptr};
                    if (OrderedListParser::is_start_line(line))
                        parser = this->create_ordered_list_parser();
                    else if (UnorderedListParser::is_start_line(line))
                        parser = this->create_unordered_list_parser();
                    return parser;
                });
        }
    };
}
#endif // LL_MD_PARSER
#else
#error Use a compiler that supports C++ 17.
#endif // C++ 17
