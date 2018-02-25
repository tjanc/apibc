// core/mson/mson_fusion.hpp
//
// (c) 2018 Thomas Jandecka
//

#ifndef APIBC_CORE_MSON_MSON_FUSION_H
#define APIBC_CORE_MSON_MSON_FUSION_H

#include <boost/fusion/adapted.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include "mson.hpp"

// clang-format off
BOOST_FUSION_ADAPT_STRUCT(
    apibc::core::mson::type_def
)

BOOST_FUSION_ADAPT_STRUCT(
    apibc::core::mson::named_type,
    (std::string, name)
    (apibc::core::mson::type_def, type)
)
// clang-format on

#endif

