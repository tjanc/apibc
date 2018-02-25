#include <fstream>
#include <iterator>

#define BOOST_SPIRIT_DEBUG

#include <backend/canonical.hpp>
#include <parser/apib_parser.hpp>

int main(int argc, char* argv[])
{
    using namespace apibc;

    if (argc != 2) {
        std::cerr << "Exactly one path expected on input\n";
        return 2;
    }

    std::ifstream file(argv[1], std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file " << argv[1] << "\n";
        return 3;
    }
    file.unsetf(std::ios::skipws);
    std::string mapped_file(                  //
        (std::istream_iterator<char>{file}),  //
        std::istream_iterator<char>{}         //
    );

    core::apib::document result;
    if (!parser::parse_apib(      //
            mapped_file.begin(),  //
            mapped_file.end(),    //
            result))              //
    {
        std::cerr << "Error parsing file " << argv[1] << "\n";
        return 1;
    }

    backend::serialize(std::cout, result);  // TODO check result

    return 0;
}
