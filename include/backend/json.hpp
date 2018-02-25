// backend/json.hpp
//
// (c) 2018 Thomas Jandecka
//

#ifndef APIBC_BACKEND_JSON_H
#define APIBC_BACKEND_JSON_H

#include <iostream>

#include <core/elements/elements.hpp>

namespace apibc
{
    namespace backend
    {
        std::ostream& serialize_json(std::ostream& out, const core::elements::document& doc);
    }
}

#endif
