//
// Created by shurj on 29-Sep-2024.
//

#ifndef SHAPES_UTILS_H
#define SHAPES_UTILS_H

#include <string>
#include <fstream>
#include <sstream>

/**
 * Reads the entire contents of a file into the output string. Only use with trusted data sources.
 *
 * @param path
 * @return The contents of the file.
 */
std::string ReadFile(const std::string &path);

#endif //SHAPES_UTILS_H
