#include "FileUtils.h"

#include <fstream>

bool Kangaroo::FileUtils::fileExists(const char* path) const {
    std::ifstream inputStream(path);
    return inputStream.is_open();
}