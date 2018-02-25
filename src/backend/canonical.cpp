// backend/canonical.cpp
//
// (c) 2018 Thomas Jandecka
//

#include <cassert>

#include "backend/canonical.hpp"

using namespace apibc::backend;
using namespace apibc::core::apib;

namespace
{
    std::ostream& serialize_section(std::ostream& out,
                                    const metadata_section& section)
    {
        for(const auto& entry : section.entries)
            out << entry.key << ": " << entry.value << '\n';
        out << '\n';
        return out;
    }

    std::ostream& serialize_section(std::ostream& out,
                                    const name_section& section)
    {
        out << "# " << section.name << '\n';
        out << section.description << "\n\n";
        return out;
    }
}

std::ostream& apibc::backend::serialize_canonical(std::ostream& out, const document& doc)
{
    if (doc.metadata) serialize_section(out, *doc.metadata);

    if (doc.name) serialize_section(out, *doc.name);

    for (const auto& section : doc.sections) {
        assert(false);  // TODO @tjanc@ not implemented
    }

    return out;
}
