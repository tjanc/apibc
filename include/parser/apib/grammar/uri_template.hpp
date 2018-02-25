// parser/apib/grammar/uri_template.hpp
//
// (c) 2018 Thomas Jandecka
//

#ifndef APIBC_PARSER_APIB_URI_TEMPLATE_H
#define APIBC_PARSER_APIB_URI_TEMPLATE_H

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_symbols.hpp>

#include <core/apib/apib_fusion.hpp>

namespace apibc
{
    namespace parser
    {
        namespace apib
        {
            namespace grammar
            {
                template <typename It,
                          typename Skipper = boost::spirit::qi::space_type>
                struct uri_template_parser
                    : boost::spirit::qi::grammar<It, core::apib::uritemplate(),
                                                 Skipper> {
                    uri_template_parser()
                        : uri_template_parser::base_type(start, "uri-template")
                    {
                        using namespace boost::spirit::qi;

                        using namespace core::apib;

                        /* - DATA - */
                        modifier.add                                 //
                            ("#", uritemplatevar::op::fragment)      //
                            ("+", uritemplatevar::op::reserved)      //
                            ("?", uritemplatevar::op::query)         //
                            ("&", uritemplatevar::op::continuation)  //
                            ;

                        /* - GRAMMAR - */
                        start %= eps > +(variable | segment);

                        variable %= no_skip['{'] > no_skip[modifier] >
                                    no_skip[variable_name] > no_skip['}'];

                        segment %= lexeme[*(char_ - '{' - space)];

                        variable_name %=
                            lexeme[*(*(alnum + digit) +
                                     (char_('%') > xdigit >> xdigit))];

                        /* - ERROR handling - */
                        variable.name("uri-template-variable-declaration");
                        variable_name.name("uri-template-variable-name");
                        segment.name("uri-template-segment");
                    }

                    boost::spirit::qi::rule<  //
                        It, std::string(), Skipper>
                        segment;

                    boost::spirit::qi::rule<  //
                        It, std::string(), Skipper>
                        variable_name;

                    boost::spirit::qi::rule<  //
                        It, core::apib::uritemplatevar(), Skipper>
                        variable;

                    boost::spirit::qi::rule<  //
                        It, core::apib::uritemplate(), Skipper>
                        start;

                    boost::spirit::qi::symbols<  //
                        char, core::apib::uritemplatevar::op>
                        modifier;
                };
            }
        }
    }
}

#endif
