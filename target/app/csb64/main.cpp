#include <iostream>
#include <vector>
#include <string>

#ifdef _WIN32
#include <io.h>
#include <fcntl.h>
#endif

#include "csb64_logic/constant/help_info_message.h"
#include "csb64_logic/run_csb64.h"

int main(int argc, char **argv)
{
    /* 
     * If we are on Windows, we need to set standard input/output modes to 
     * binary so program doesn't stop at the SUB character (not applicable to
     * Linux). 
     */
    #ifdef _WIN32
    _setmode(_fileno(stdin), _O_BINARY);
    _setmode(_fileno(stdout), _O_BINARY);
    #endif

    // Working with vector of string is easier (and safer).
    std::vector<std::string> user_args{};
    for (long long index{0}; index < argc; ++index)
    {
        user_args.push_back(argv[index]);
    };

    const auto stdin_reader{[]() -> int
    {
        return std::cin.get();
    }};

    const auto stdout_writer{[](const unsigned char character) -> void
    {
        std::cout << character;
    }};

    const auto stdin_at_eof{[]() -> bool
    {
        return std::cin.eof();
    }};

    const auto error_printer{[](const std::string& input) -> void
    {
        std::cerr << input;
    }};

    const auto help_printer{[]() -> void
    {
        std::cout << csb64_logic::constant::help_info_message();
    }};

    return csb64_logic::run_csb64(
        user_args,
        stdin_reader,
        stdout_writer,
        stdin_at_eof,
        error_printer,
        help_printer
    );
};
