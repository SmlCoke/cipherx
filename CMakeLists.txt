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