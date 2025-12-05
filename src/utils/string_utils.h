#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string>
#include <vector>

// 分割字符串
std::vector<std::string> split(const std::string& str, char delimiter = ' ');

// 去除字符串首尾空格
std::string trim(const std::string& str);

#endif