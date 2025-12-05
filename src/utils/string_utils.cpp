#include "string_utils.h"
#include <sstream>
#include <algorithm>

// 1205: 
// 分割字符串
// C++中的std::string本身没有像“读取下一个单词”或“读取特定字符”这样的流式操作方法。通过将字符串放入 istringstream，我们可以像操作 cin（标准输入）或文件流一样来操作这个字符串。
// std::getline(): 用于从“流”中读取字符，可以是iostream，fstream，这里用到的是istringstream
std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens; // 1205: 存放命令块的列表
    std::string token; // 1205: 命令块
    std::istringstream tokenStream(str); // 1205: 把原始命令转化为流，便于读取

    // 1205: getline(a, b, c): 从流a中依次读取字符串，放到b中，直到我们遇到分隔符：c
    while (std::getline(tokenStream, token, delimiter)) {
        if (!token.empty()) {
            // 1205: 如果两个分隔符紧挨着（例如 "a,,b"），getline 会读出一个空字符串
            // 1205: 这里的判断是为了忽略这些空结果
            tokens.push_back(token);
        }
    }
    
    return tokens;
}

// 1205: 去除字符串首尾空格
std::string trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\n\r");
    if (start == std::string::npos) {
        return "";
    }
    
    size_t end = str.find_last_not_of(" \t\n\r");
    return str.substr(start, end - start + 1);
    // 1205: std.substr(start, length): 从start位置开始，读取length个字符
}