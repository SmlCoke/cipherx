#include <iostream>
#include <vector>
#include <cassert>
#include "../utils/string_utils.h"

// 确保控制台编码为UTF-8
// [修改] 跨平台兼容的头文件引入
// 只有在 Windows 系统下，编译器才会读取这一段
#ifdef _WIN32
    #include <windows.h>
#endif

// [新增] 一个专门用于初始化控制台的辅助函数
void init_console_encoding() {
    #ifdef _WIN32
        // Windows: 强制设置控制台代码页为 UTF-8 (65001)
        SetConsoleOutputCP(65001);
        SetConsoleCP(65001); // 设置输入也为 UTF-8
    #else
        // Linux / macOS: 默认通常就是 UTF-8，但在某些环境下可能需要设置 locale
        // std::setlocale(LC_ALL, ""); 
    #endif
}

int main() {
    // [调用] 初始化控制台编码为UTF-8
    init_console_encoding();

    // 测试 split 函数
    std::string str = "hello world this is a test";
    char delimiter = ' ';
    std::vector<std::string> result = split(str, delimiter);
    assert(result.size() == 6);
    assert(result[0] == "hello");
    assert(result[1] == "world");
    assert(result[2] == "this");
    assert(result[3] == "is");
    assert(result[4] == "a");
    assert(result[5] == "test");

    // 测试 trim 函数
    std::string whitespace = "   hello world   ";
    std::string trimmed = trim(whitespace);
    assert(trimmed == "hello world");

    // [保留] 现在可以放心地输出中文了
    std::cout << "全部测试通过！" << std::endl;
    return 0;
}