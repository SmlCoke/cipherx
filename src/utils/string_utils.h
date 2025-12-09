#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string>
#include <vector>

// 分割字符串
std::vector<std::string> split(const std::string& str, char delimiter = ' ');

// [新增] 智能解析命令行，支持双引号包含空格的参数
// 例如: e caesar "hello world" -> ["e", "caesar", "hello world"]
std::vector<std::string> parseCommandLine(const std::string& line);


// 去除字符串首尾空格
std::string trim(const std::string& str);

#endif