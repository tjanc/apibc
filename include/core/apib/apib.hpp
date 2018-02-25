// core/apib/apib.hpp
//
// OPTIM: store descriptions, payload and schema as byte offset in source file -
// no need to load potentially long string never to be interpreted
//
// (c) 2018 Thomas Jandecka
//

#ifndef APIBC_PARSER_APIB_APIB_H
#define APIBC_PARSER_APIB_APIB_H

#include <boost/optional.hpp>
#include <string>
#include <variant>
#include <vector>

#include "../mson/mson.hpp"

namespace apibc
{
    namespace core
    {
        namespace apib
        {
            struct uritemplatevar {
                enum class op { fragment, reserved, query, continuation };
                std::string name;
            };

            struct uritemplate {
                using segment = std::variant<std::string, uritemplatevar>;
                std::vector<segment> segments;
            };

            struct uriparam {
                std::string name;
                boost::optional<std::string> inline_description;
                boost::optional<std::string> description;
                boost::optional<std::string> default_value;
                boost::optional<std::string> example_value;
                boost::optional<std::string> type;
                std::vector<std::string> members;
                bool required;
                bool optional;
            };

            struct uriparams_section {
                std::vector<uriparam> params;
            };

            struct attributes_section {
                mson::type_def type;
            };

            struct headers_section {
                struct entry {
                    std::string key;
                    std::string value;
                };
                std::vector<entry> params;
            };

            struct body_section {
                std::string payload;
            };

            struct schema_section {
                std::string schema;
            };

            struct model_section {
                boost::optional<headers_section> headers;
                boost::optional<attributes_section> attributes;
                boost::optional<body_section> body;
                boost::optional<schema_section> schema;
            };

            struct relation_section {
                std::string identifier;
            };

            struct request_section {
                boost::optional<headers_section> headers;
                boost::optional<attributes_section> attributes;
                boost::optional<body_section> body;
                boost::optional<schema_section> schema;
            };

            struct response_section {
                boost::optional<headers_section> headers;
                boost::optional<attributes_section> attributes;
                boost::optional<body_section> body;
                boost::optional<schema_section> schema;
            };

            struct action_section {
                boost::optional<relation_section> relation;
                boost::optional<uriparams_section> uriparams;
                boost::optional<attributes_section> attributes;
                std::vector<request_section> requests;
                std::vector<response_section> responses;
            };

            struct metadata_section {
                struct entry {
                    std::string key;
                    std::string value;
                };
                std::vector<entry> entries;
            };

            struct name_section {
                std::string name;
                std::string description;
            };

            struct resource_section {
                boost::optional<uriparams_section> uriparams;
                boost::optional<attributes_section> attributes;
                boost::optional<model_section> model;
                std::vector<action_section> actions;
            };

            struct resource_group_section {
                std::vector<resource_section> resources;
            };

            struct datastructure_section {
                std::vector<mson::named_type> resources;
            };

            struct document {
                using tail_section = std::variant<  //
                    resource_section,               //
                    resource_group_section,         //
                    datastructure_section>;

                boost::optional<metadata_section> metadata;
                boost::optional<name_section> name;
                std::vector<tail_section> sections;
            };
        }
    }
}

#endif
