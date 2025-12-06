cmake_minimum_required(VERSION 3.10)

project(cipherx)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 包含头文件目录
include_directories(src)

# 启用测试功能
enable_testing()

# ==========================================
# 1. 定义库文件
# ==========================================

# 1.1 工具库 (utils)
add_library(utils_lib src/utils/string_utils.cpp)

# 1.2 [新增] 加密算法库 (cipher)
# 将 caesar.cpp 编译成静态库
add_library(cipher_lib src/cipher/caesar.cpp)

# ==========================================
# 2. 主程序 (cipherx)
# ==========================================
add_executable(cipherx src/main.cpp)

# 链接所有需要的库
# 主程序既需要字符串工具，也需要加密算法
target_link_libraries(cipherx utils_lib cipher_lib)

# ==========================================
# 3. 测试程序
# ==========================================

# 3.1 String Utils 测试
add_executable(test_string_utils tests/test_string_utils.cpp)
target_link_libraries(test_string_utils utils_lib)
add_test(NAME StringUtilsTest COMMAND test_string_utils)

# 3.2 [新增] Caesar Cipher 测试
add_executable(test_caesar tests/test_caesar.cpp)
# 测试程序需要链接 cipher_lib 才能调用 Caesar 类
target_link_libraries(test_caesar cipher_lib)
# 注册测试用例，名称为 CaesarTest
add_test(NAME CaesarTest COMMAND test_caesar)