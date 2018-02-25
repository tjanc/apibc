// core/mson/mson.hpp
//
// (c) 2018 Thomas Jandecka
//

#ifndef APIBC_CORE_MSON_MSON_H
#define APIBC_CORE_MSON_MSON_H

#include <string>

namespace apibc
{
    namespace core
    {
        namespace mson
        {
            struct type_def {
                // TODO
            };

            struct named_type {
                std::string name;
                type_def type;
            };
        }
    }
}

#endif
