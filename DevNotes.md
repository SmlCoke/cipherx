# 开发笔记

## CMake 配置
```cmake
cmake_minimum_required(VERSION 3.10)

project(cipherx)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 包含头文件目录
include_directories(src)

# [新增] 启用测试功能
enable_testing()

# 1. 定义库文件 (utils)
# 将 string_utils 编译成一个静态库，方便主程序和测试程序复用
add_library(utils_lib src/utils/string_utils.cpp)
# add_library(utils_lib ...)：告诉 CMake，先把 string_utils.cpp 编译好，打包成一个叫 utils_lib 的库。

# 2. 主程序
add_executable(cipherx src/main.cpp)
# 链接 utils 库
target_link_libraries(cipherx utils_lib)
# target_link_libraries(cipherx utils_lib)：告诉 CMake，生成 cipherx 可执行文件时，把 utils_lib 里的代码“粘贴”进去。

# 3. 测试程序 (test_string_utils)
add_executable(test_string_utils src/test/test_string_utils.cpp)
# 链接 utils 库
target_link_libraries(test_string_utils utils_lib)
# target_link_libraries(test_string_utils utils_lib)：生成测试程序时，也把 utils_lib “粘贴”进去。

# [新增] 注册测试用例
# 这样用户在终端输入 "ctest" 即可运行此测试，无需手动执行 ./bin/test_string_utils
add_test(NAME StringUtilsTest COMMAND test_string_utils)
```

1. 使用 `add_library` 构建静态链接库，方便：(1) 编译多个源文件 (2) 代码复用，不用每次都编译 (3) 测试不同原文件
2. 不同源文件的测试方法：CTest
   在CMakeLists.txt这样设置：
   ```cmake
   enable_testing()
   add_test(NAME StringUtilsTest COMMAND test_string_utils)
   ```
   在终端中，build路径下，输入`ctest`即可看到是否所有测试通过，输入`ctest -V`可以看到详细的测试输出信息。

## 控制台兼容中文（UTF-8）
```cpp
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
```

原理说明：
1. 当在 Windows 上编译时，_WIN32 被定义，编译器会包含 <windows.h> 并执行 SetConsoleOutputCP。
2. 当在 Linux/GitHub Actions 上编译时，_WIN32 未定义，编译器会直接忽略那几行代码，从而不会报错。

## 命令行解析参数——ToLower的问题：
```cpp
// 辅助函数：将字符串转换为小写
string toLowerCase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}
↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
// 辅助函数：将字符串转换为小写
string toLowerCase(string str) {
    // [修改] 使用 lambda 表达式并强制转换为 unsigned char，这是 C++ 标准推荐的安全做法
    transform(str.begin(), str.end(), str.begin(), [](unsigned char c){ 
        return std::tolower(c); 
    });
    return str;
}
```
问题： 在 toLowerCase 函数中，::tolower 接受 int 参数。在某些平台上，如果 char 是有符号的（signed char）且包含非 ASCII 字符（例如用户不小心输入了中文），它可能被转换为负整数，导致 ::tolower 发生未定义行为（崩溃或乱码）。
修复建议： 在调用 tolower 之前，将字符强制转换为 unsigned char。