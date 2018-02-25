// parser/apib/grammar/document.hpp
//
// (c) 2018 Thomas Jandecka
//

#ifndef APIBC_PARSER_APIB_GRAMMAR_DOCUMENT_H
#define APIBC_PARSER_APIB_GRAMMAR_DOCUMENT_H

#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_optional.hpp>
#include <boost/spirit/include/qi_symbols.hpp>

#include <core/apib/apib_fusion.hpp>

#include "keywords.hpp"
#include "uri_template.hpp"

namespace apibc
{
    namespace parser
    {
        namespace apib
        {
            namespace grammar
            {
                template <typename T>
                struct name_of {
                };

                template <>
                struct name_of<core::apib::name_section> {
                    static constexpr const char* value = "name";
                };

                // template <typename Section, typename It,
                //           typename Skipper = boost::spirit::qi::space_type>
                // struct section_parser
                //     : boost::spirit::qi::grammar<
                //           It, Section(),
                //           boost::spirit::qi::locals<unsigned> Skipper> {

                //     section_parser()
                //         : section_parser::base_type(section,
                //                                     name_of<Section>::value)
                //     {
                //     }

                //     boost::spirit::qi::rule<It, Section(), Skipper> section;
                // };

                template <typename It,
                          typename Skipper = boost::spirit::qi::space_type>
                struct resource_section_parser
                    : boost::spirit::qi::grammar<
                          It, core::apib::resource_section(), Skipper> {
                    resource_section_parser()
                        : resource_section_parser::base_type(name, "name")
                    {
                        using namespace boost::spirit::qi;
                        using namespace labels;

                        using boost::phoenix::construct;
                        using boost::phoenix::val;

                        using namespace core::apib;

                        /* - DATA - */

                        /* - GRAMMAR - */

                        /* - ERROR handling - */
                    }

                    boost::spirit::qi::rule<  //
                        It, core::apib::resource_section(), Skipper>
                        name;

                    boost::spirit::qi::rule<  //
                        It, std::string(), Skipper>
                        section_identifier;

                    uri_template_parser<It, Skipper> uri_template;

                    list_keyword_parser keyword;
                };

                template <typename It,
                          typename Skipper = boost::spirit::qi::space_type>
                struct name_section_parser
                    : boost::spirit::qi::grammar<It, core::apib::name_section(),
                                                 Skipper> {
                    name_section_parser()
                        : name_section_parser::base_type(name, "name")
                    {
                        using namespace boost::spirit::qi;
                        using namespace labels;

                        using boost::phoenix::construct;
                        using boost::phoenix::val;

                        using namespace core::apib;

                        /* - GRAMMAR - */

                        section_identifier = lexeme[  //
                            +(char_ - '\n' - '[' - ']' - '(' - ')' - keyword)];

                        name %=                           //
                            '#' >>                        //
                            section_identifier >>         //
                            lexeme[+(char_ - "\n\n")] >>  //
                            no_skip["\n\n"];

                        /* - ERROR handling - */

                        section_identifier.name("section identifier");

                        on_error<fail>(
                            name,
                            std::cerr
                                << val("Expecting ") << _4  // what failed?
                                << val(" here: \"")
                                << construct<std::string>(
                                       _3, _2)  // iterators to error-pos, end
                                << val("\"") << std::endl);
                    }

                    boost::spirit::qi::rule<  //
                        It, core::apib::name_section(), Skipper>
                        name;

                    boost::spirit::qi::rule<  //
                        It, std::string(), Skipper>
                        section_identifier;

                    list_keyword_parser keyword;
                };

                template <typename It,
                          typename Skipper = boost::spirit::qi::space_type>
                struct document_parser
                    : boost::spirit::qi::grammar<It, core::apib::document(),
                                                 Skipper> {
                    document_parser()
                        : document_parser::base_type(start, "api-blueprint")
                    {
                        using namespace boost::spirit::qi;

                        using boost::phoenix::construct;
                        using boost::phoenix::val;

                        metadata_entry =                            //
                            lexeme[+(char_ - ':' - '\n' - '#')] >>  //
                            no_skip[':'] >>                         //
                            lexeme[+(char_ - '\n')] >>              //
                            no_skip['\n'];

                        start %=          //
                            -(eps >> +metadata_entry) >>  //
                            -name >>      //
                            *(resource | resource_group | datastructure);

                        metadata.name("metadata-section");
                        metadata_entry.name("metadata-section-entry");

                        on_error<fail>(
                            start,
                            std::cerr
                                << val("Expecting ") << _4  // what failed?
                                << val(" here: \"")
                                << construct<std::string>(
                                       _3, _2)  // iterators to error-pos, end
                                << val("\"") << std::endl);
                    }

                    boost::spirit::qi::rule<  //
                        It, core::apib::document(), Skipper>
                        start;

                    boost::spirit::qi::rule<  //
                        It, core::apib::metadata_section(), Skipper>
                        metadata;

                    boost::spirit::qi::rule<  //
                        It, core::apib::metadata_section::entry(), Skipper>
                        metadata_entry;

                    name_section_parser<  //
                        It, Skipper>
                        name;

                    boost::spirit::qi::rule<  //
                        It, core::apib::resource_section(), Skipper>
                        resource;

                    boost::spirit::qi::rule<  //
                        It, core::apib::resource_group_section(), Skipper>
                        resource_group;

                    boost::spirit::qi::rule<  //
                        It, core::apib::datastructure_section(), Skipper>
                        datastructure;
                };
            }
        }
    }
}

#endif
