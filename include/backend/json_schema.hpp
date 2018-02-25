// backend/json_schema.hpp
//
// (c) 2018 Thomas Jandecka
//

#ifndef APIBC_BACKEND_JSON_SCHEMA_H
#define APIBC_BACKEND_JSON_SCHEMA_H

#include <iostream>

#include <core/elements/elements.hpp>

namespace apibc
{
    namespace backend
    {
        std::ostream& serialize_json_schema(std::ostream& out, const core::elements::document& doc);
    }
}

#endif
