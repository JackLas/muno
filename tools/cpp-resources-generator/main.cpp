// Copyright (c) 2025 Yevhenii Kryvyi
// SPDX-License-Identifier: MIT

#include <filesystem>
#include <iostream>

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        std::cerr << "Not enough arguments: " << argc << std::endl;
        return 1;
    }

    std::filesystem::path input{argv[1]};
    std::filesystem::path output{argv[2]};

    std::cout << " - Copy from '" << input << "' to '" << output << "'\n";

    std::filesystem::copy(input, output);

    return 0;
}