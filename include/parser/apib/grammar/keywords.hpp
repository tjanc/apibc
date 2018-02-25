// parser/apib/grammar/keywords.hpp
//
// (c) 2018 Thomas Jandecka
//

#ifndef APIBC_PARSER_APIB_KEYWORDS_H
#define APIBC_PARSER_APIB_KEYWORDS_H

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_symbols.hpp>

#include "uri_template.hpp"

namespace apibc
{
    namespace parser
    {
        namespace apib
        {
            namespace grammar
            {
                enum class list_keyword {
                    request,     //
                    response,    //
                    body,        //
                    schema,      //
                    model,       //
                    header,      //
                    headers,     //
                    parameter,   //
                    parameters,  //
                    values,      //
                    attribute,   //
                    attributes,  //
                    relation     //
                };

                struct list_keyword_parser
                    : boost::spirit::qi::symbols<char, list_keyword> {
                    list_keyword_parser()
                    {
                        add                                           //
                            ("Request", list_keyword::request)        //
                            ("Response", list_keyword::response)      //
                            ("Body", list_keyword::body)              //
                            ("Schema", list_keyword::schema)          //
                            ("Model", list_keyword::model)            //
                            ("Header", list_keyword::header)          //
                            ("Headers", list_keyword::headers)        //
                            ("Parameter", list_keyword::parameter)    //
                            ("Parameters", list_keyword::parameters)  //
                            ("Values", list_keyword::values)          //
                            ("Attribute", list_keyword::attribute)    //
                            ("Attributes", list_keyword::attributes)  //
                            ("Relation", list_keyword::relation)      //
                            ;
                    }
                };

                enum class http_method {
                    connect,  //
                    del,      //
                    get,      //
                    head,     //
                    options,  //
                    patch,    //
                    post,     //
                    put,      //
                    trace     //
                };

                struct http_method_parser
                    : boost::spirit::qi::symbols<char, http_method> {
                    http_method_parser()
                    {
                        add                                    //
                            ("CONNECT", http_method::connect)  //
                            ("DELETE", http_method::del)       //
                            ("GET", http_method::get)          //
                            ("HEAD", http_method::head)        //
                            ("OPTIONS", http_method::options)  //
                            ("PATCH", http_method::patch)      //
                            ("POST", http_method::post)        //
                            ("PUT", http_method::put)          //
                            ("TRACE", http_method::trace)      //
                            ;
                    }
                };

                enum class header_keyword {
                    group,            //
                    data_structures,  //
                };

                struct header_keyword_parser
                    : boost::spirit::qi::symbols<char, header_keyword> {
                    header_keyword_parser()
                    {
                        add                                   //
                            ("Group", header_keyword::group)  //
                            ("Data Structures",
                             header_keyword::data_structures)  //
                            ;
                    }
                };

                template <typename It,
                          typename Skipper = boost::spirit::qi::space_type>
                struct section_keyword_parser
                    : boost::spirit::qi::grammar<It, void(), Skipper> {
                    section_keyword_parser()
                        : section_keyword_parser::base_type(start,
                                                            "section-keyword")
                    {
                        using namespace boost::spirit::qi;

                        /* - GRAMMAR - */
                        start %= (header_keyword                    //
                                  | (http_method > -uri_template))  //
                                 | (uri_template)                   //
                            ;

                        /* - ERROR handling - */
                    }

                    boost::spirit::qi::rule<  //
                        It, core::apib::uritemplate(), Skipper>
                        start;

                    header_keyword_parser header_keyword;
                    http_method_parser http_method;
                    uri_template_parser<It, Skipper> uri_template;
                };
            }
        }
    }
}

#endif
