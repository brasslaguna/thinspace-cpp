
#ifndef THINSPACE_UTIL_FILE_H_
#define THINSPACE_UTIL_FILE_H_

#include <stdio.h>
#include <string>
#include <fstream>

namespace util {
namespace file {

std::string Load(const std::string& file_path);

} // namespace file
} // namespace util

#endif // THINSPACE_UTIL_FILE_H_