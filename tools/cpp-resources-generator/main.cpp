// Copyright (c) 2025 Yevhenii Kryvyi
// SPDX-License-Identifier: MIT

#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <regex>
#include <stdexcept>
#include <string>

#define LOG(output) std::output << TARGET_NAME ": "

namespace
{
constexpr const char* PLACEHOLDER_ANCHOR = "MUNO-GEN-PH";

struct Config
{
    std::filesystem::path inputTemplate;
    std::filesystem::path resourcesDir;
    std::filesystem::path outputFile;
    std::filesystem::path outputTmpfile;
};

Config processArgs(const int argc, const char** argv)
{
    if (argc < 4)
    {
        throw std::runtime_error("not enough arguments");
    }
    Config config;

    config.inputTemplate = argv[1];
    config.resourcesDir = argv[2];
    config.outputFile = argv[3];
    config.outputTmpfile = config.outputFile.parent_path() /
                           ("wip-gen-" + std::to_string(std::time(nullptr)) + ".cpp");

    return config;
}

std::optional<std::tuple<std::string, std::string, std::filesystem::path>>
getPlaceholderInfo(const std::string& line)
{
    static const std::regex rgx(std::string("//\\s*") + PLACEHOLDER_ANCHOR +
                                "\\s*:\\s*(.*)~(.*)~(.*)");
    std::smatch matches;

    if (!std::regex_search(line, matches, rgx) || matches.size() != 4)
    {
        return std::nullopt;
    }

    std::string_view trimLine = line;
    trimLine.remove_prefix(std::min(trimLine.find_first_not_of(" "), trimLine.size()));

    LOG(cout) << "detected " << trimLine << std::endl;

    return std::tuple{matches[1].str(), matches[2].str(), matches[3].str()};
}

std::stringstream generateEmbeddedResource(const Config& cfg, const std::string& varname,
                                           const std::string sizename,
                                           const std::filesystem::path& resource)
{
    const std::filesystem::path resourceFullPath = cfg.resourcesDir / resource;
    if (!std::filesystem::exists(resourceFullPath))
    {
        throw std::runtime_error(resource.string() + " doesn't exist");
    }

    std::ifstream resourceBin(resourceFullPath, std::ios::binary);
    if (!resourceBin)
    {
        throw std::runtime_error("unable to open " + resource.string());
    }

    std::stringstream stream;
    stream << "static const unsigned char ";

    stream << varname << "[] = {";

    char byte;
    while (resourceBin.get(byte))
    {
        stream << "0x" << std::hex << std::setw(2) << std::setfill('0')
               << (static_cast<int>(byte) & 0xFF) << ", ";
    }

    stream << "};";

    stream << "\n";

    stream << "static std::size_t " << sizename << " = sizeof(" << varname << ")/sizeof(" << varname
           << "[0]);";

    return stream;
}

} // namespace

int main(const int argc, const char** argv)
try
{
    LOG(cout) << "started\n";
    const auto config = processArgs(argc, argv);
    LOG(cout) << "config:\n"
              << "\tinputTemplate: " << config.inputTemplate
              << "\n\tresourceDir: " << config.resourcesDir
              << "\n\toutputFile: " << config.outputFile << std::endl;

    std::ofstream output{config.outputTmpfile};
    output << "// generated with " << TARGET_NAME << "\n\n";

    std::ifstream input{config.inputTemplate};

    std::string line;
    while (!input.eof())
    {
        std::getline(input, line);

        const auto placeholder = getPlaceholderInfo(line);
        if (!placeholder.has_value())
        {
            output << line << '\n';
            continue;
        }

        const auto& [varname, sizename, filepath] = placeholder.value();
        output << generateEmbeddedResource(config, varname, sizename, filepath).rdbuf() << '\n';
    }

    input.close();
    output.close();

    std::filesystem::rename(config.outputTmpfile, config.outputFile);

    return 0;
}
catch (const std::exception& ex)
{
    LOG(cerr) << "error - " << ex.what() << std::endl;
    return 1;
}