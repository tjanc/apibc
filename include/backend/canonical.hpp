// parser/apib/grammar/document.hpp
//
// (c) 2018 Thomas Jandecka
//

#ifndef APIBC_BACKEND_CANONICAL_H
#define APIBC_BACKEND_CANONICAL_H

#include <iostream>

#include <core/apib/apib.hpp>

namespace apibc
{
    namespace backend
    {
        std::ostream& serialize(std::ostream& out, const core::apib::document& doc);
    }
}

#endif
