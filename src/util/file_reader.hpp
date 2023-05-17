#pragma once

#include <filesystem>
#include <fstream>
#include <ios>
#include <memory>

namespace util {

std::unique_ptr<char[]> read_from_file(std::filesystem::path file_path);

} // namespace util
