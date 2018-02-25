// core/interpreter.hpp
//
// (c) 2018 Thomas Jandecka
//

#ifndef APIBC_CORE_INTERPRETER_H
#define APIBC_CORE_INTERPRETER_H

#include "apib/apib.hpp"
#include "elements/elements.hpp"

namespace apibc
{
    namespace core
    {
        ///
        /// Interpret a API Blueprint document as API Elements.
        ///
        /// @param  doc API Blueprint AST to be transformed
        /// @result API Elements representing given API Blueprint deocument
        ///
        elements::object interpret(const apib::document& doc);
    }
}

#endif
