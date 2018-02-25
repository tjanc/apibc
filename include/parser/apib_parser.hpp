// parser/apib_parser.hpp
//
// (c) 2018 Thomas Jandecka
//

#ifndef APIBC_PARSER_APIB_PARSER_H
#define APIBC_PARSER_APIB_PARSER_H

#include <core/apib/apib.hpp>

#include <boost/spirit/include/qi.hpp>
#include "apib/grammar/document.hpp"

namespace apibc
{
    namespace parser
    {
        template <typename It>
        bool parse_apib(It first, It last, core::apib::document& api)
        {
            using namespace apib::grammar;
            using namespace boost::spirit::qi;

            using ascii_space_type = boost::spirit::ascii::space_type;
            constexpr auto ascii_space = boost::spirit::ascii::space;

            //document_parser<It> parser;
            document_parser<It, ascii_space_type> parser;

            return phrase_parse(first, last, parser, ascii_space, api);
        }
    }
}

#endif
