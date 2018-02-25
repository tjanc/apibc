// core/apib/apib_fusion.hpp
//
// (c) 2018 Thomas Jandecka
//

#ifndef APIBC_CORE_APIB_APIB_FUSION_H
#define APIBC_CORE_APIB_APIB_FUSION_H

#include <boost/fusion/adapted.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
//#include <boost/fusion/include/io.hpp>

#include <core/mson/mson_fusion.hpp>
#include "apib.hpp"

// clang-format off
BOOST_FUSION_ADAPT_STRUCT(
    apibc::core::apib::uriparam,
    (std::string, name)
    (boost::optional<std::string>, inline_description)
    (boost::optional<std::string>, description)
    (boost::optional<std::string>, default_value)
    (boost::optional<std::string>, example_value)
    (boost::optional<std::string>, type)
    (std::vector<std::string>, members)
    (bool, required)
    (bool, optional)
)

BOOST_FUSION_ADAPT_STRUCT(
    apibc::core::apib::uriparams_section,
    (std::vector<apibc::core::apib::uriparam>, params)
)

BOOST_FUSION_ADAPT_STRUCT(
    apibc::core::apib::metadata_section::entry,
    (std::string, key)
    (std::string, value)
)

BOOST_FUSION_ADAPT_STRUCT(
    apibc::core::apib::metadata_section,
    (std::vector<apibc::core::apib::metadata_section::entry>, entries)
)

BOOST_FUSION_ADAPT_STRUCT(
    apibc::core::apib::attributes_section,
    (apibc::core::mson::type_def, type)
)

BOOST_FUSION_ADAPT_STRUCT(
    apibc::core::apib::headers_section::entry,
    (std::string, key)
    (std::string, value)
)

BOOST_FUSION_ADAPT_STRUCT(
    apibc::core::apib::headers_section,
    (std::vector<apibc::core::apib::headers_section::entry>, params)
)

BOOST_FUSION_ADAPT_STRUCT(
    apibc::core::apib::body_section,
    (std::string, payload)
)

BOOST_FUSION_ADAPT_STRUCT(
    apibc::core::apib::schema_section,
    (std::string, schema)
)

BOOST_FUSION_ADAPT_STRUCT(
    apibc::core::apib::model_section,
    (boost::optional<apibc::core::apib::headers_section>, headers)
    (boost::optional<apibc::core::apib::attributes_section>, attributes)
    (boost::optional<apibc::core::apib::body_section>, body)
    (boost::optional<apibc::core::apib::schema_section>, schema)
)

BOOST_FUSION_ADAPT_STRUCT(
    apibc::core::apib::relation_section,
    (std::string, identifier)
)

BOOST_FUSION_ADAPT_STRUCT(
    apibc::core::apib::request_section,
    (boost::optional<apibc::core::apib::headers_section>, headers)
    (boost::optional<apibc::core::apib::attributes_section>, attributes)
    (boost::optional<apibc::core::apib::body_section>, body)
    (boost::optional<apibc::core::apib::schema_section>, schema)
)

BOOST_FUSION_ADAPT_STRUCT(
    apibc::core::apib::response_section,
    (boost::optional<apibc::core::apib::headers_section>, headers)
    (boost::optional<apibc::core::apib::attributes_section>, attributes)
    (boost::optional<apibc::core::apib::body_section>, body)
    (boost::optional<apibc::core::apib::schema_section>, schema)
)

BOOST_FUSION_ADAPT_STRUCT(
    apibc::core::apib::action_section,
    (boost::optional<apibc::core::apib::relation_section>, relation)
    (boost::optional<apibc::core::apib::uriparams_section>, uriparams)
    (boost::optional<apibc::core::apib::attributes_section>, attributes)
    (std::vector<apibc::core::apib::request_section>, requests)
    (std::vector<apibc::core::apib::response_section>, responses)
)

BOOST_FUSION_ADAPT_STRUCT(
    apibc::core::apib::name_section,
    (std::string, name)
    (std::string, description)
)

BOOST_FUSION_ADAPT_STRUCT(
    apibc::core::apib::resource_section,
    (boost::optional<apibc::core::apib::uriparams_section>, uriparams)
    (boost::optional<apibc::core::apib::attributes_section>, attributes)
    (boost::optional<apibc::core::apib::model_section>, model)
    (std::vector<apibc::core::apib::action_section>, actions)
)

BOOST_FUSION_ADAPT_STRUCT(
    apibc::core::apib::resource_group_section,
    (std::vector<apibc::core::apib::resource_section>, resources)
)

BOOST_FUSION_ADAPT_STRUCT(
    apibc::core::apib::datastructure_section,
    (std::vector<apibc::core::mson::named_type>, resources)
)

BOOST_FUSION_ADAPT_STRUCT(
    apibc::core::apib::document,
    (boost::optional<apibc::core::apib::metadata_section>, metadata)
    (boost::optional<apibc::core::apib::name_section>, name)
    (std::vector<apibc::core::apib::document::tail_section>, sections)
)
// clang-format on

#endif
