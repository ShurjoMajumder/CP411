//
// Created by shurj on 29-Sep-2024.
//

#include "utils.h"

std::string ReadFile(const std::string &path) {
    std::ifstream fileStream(path);
    std::stringstream buffer;
    buffer << fileStream.rdbuf() << '\0';

    return buffer.str();
}
