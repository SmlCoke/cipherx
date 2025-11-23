# CipherX CLI 工具开发指南

## 项目概述

CipherX 是一个交互式命令行加密/解密工具，支持多种加密算法，使用 C/C++ 实现，具有良好的性能和跨平台特性。

## 一、工具功能清单

### 1.1 核心功能

#### 基础功能
- **交互式命令行界面 (REPL)**
  - 启动工具后进入交互模式
  - 支持命令提示符显示
  - 命令历史记录（上下键导航）
  - 优雅的退出机制

- **文本加密/解密**
  - 直接加密输入的文本字符串
  - 直接解密密文字符串
  - 支持中文、英文及常用标点符号

- **文件加密/解密**
  - 读取文件内容进行加密
  - 读取文件内容进行解密
  - 保存加密/解密结果到文件

- **配置管理**
  - 加载自定义字符映射表（JSON 格式）
  - 显示当前使用的映射配置
  - 保存当前配置到文件

#### 帮助系统
- `help` 命令：显示所有可用命令
- `help <command>` 命令：显示特定命令的详细帮助

### 1.2 加密算法实现（第一版）

#### 1. 凯撒密码 (Caesar Cipher)
- **描述**：最简单的替换加密，将每个字符按照固定位移量进行替换
- **参数**：位移量（shift）
- **命令示例**：
  ```
  cipherx> encrypt caesar "Hello World" 3
  Khoor Zruog
  ```
- **实现难度**：⭐ (非常适合初学者)

#### 2. 替换密码 (Substitution Cipher)
- **描述**：使用自定义字符映射表进行一对一替换
- **参数**：映射表文件路径
- **命令示例**：
  ```
  cipherx> load mapping.json
  cipherx> encrypt substitution "Hello"
  ```
- **实现难度**：⭐⭐

#### 3. 维吉尼亚密码 (Vigenère Cipher)
- **描述**：使用密钥字符串进行多表替换加密
- **参数**：密钥字符串
- **命令示例**：
  ```
  cipherx> encrypt vigenere "Hello World" "KEY"
  ```
- **实现难度**：⭐⭐⭐

#### 4. 栅栏密码 (Rail Fence Cipher)
- **描述**：将文本按 Z 字形排列后横向读取
- **参数**：栅栏数量（rails）
- **命令示例**：
  ```
  cipherx> encrypt railfence "Hello World" 3
  ```
- **实现难度**：⭐⭐⭐

#### 5. Base64 编码
- **描述**：将文本转换为 Base64 编码（严格来说是编码而非加密）
- **参数**：无
- **命令示例**：
  ```
  cipherx> encode base64 "Hello World"
  SGVsbG8gV29ybGQ=
  ```
- **实现难度**：⭐⭐

### 1.3 后续版本扩展功能（预留设计）

#### 对称加密算法
- AES (Advanced Encryption Standard)
- DES (Data Encryption Standard)
- XOR 加密

#### 非对称加密算法
- RSA（需要第三方库支持）

#### 其他功能
- 密码强度分析
- 频率分析工具（用于破解简单密码）
- 批量文件处理
- 配置文件自动加载
- 命令脚本支持（从文件读取命令序列）

---

## 二、C/C++ 详细开发步骤

### 2.1 开发环境准备

#### Windows 平台
1. **安装编译器**
   - 推荐：MinGW-w64 或 Visual Studio Community
   - MinGW-w64 下载：https://www.mingw-w64.org/
   - 安装后将 `bin` 目录添加到 PATH 环境变量

2. **验证安装**
   ```bash
   gcc --version
   g++ --version
   ```

#### Linux 平台
1. **安装 GCC/G++**
   ```bash
   sudo apt update
   sudo apt install build-essential
   ```

2. **验证安装**
   ```bash
   gcc --version
   g++ --version
   ```

#### macOS 平台
1. **安装 Xcode Command Line Tools**
   ```bash
   xcode-select --install
   ```

2. **验证安装**
   ```bash
   gcc --version
   ```

### 2.2 项目结构设计

```
cipherx/
├── src/                    # 源代码目录
│   ├── main.cpp           # 主程序入口
│   ├── cli.cpp            # CLI 交互逻辑
│   ├── cli.h              # CLI 头文件
│   ├── cipher/            # 加密算法模块
│   │   ├── cipher_base.h  # 加密算法基类
│   │   ├── caesar.cpp     # 凯撒密码实现
│   │   ├── caesar.h
│   │   ├── substitution.cpp
│   │   ├── substitution.h
│   │   ├── vigenere.cpp
│   │   ├── vigenere.h
│   │   └── ...
│   ├── utils/             # 工具函数
│   │   ├── string_utils.cpp
│   │   ├── string_utils.h
│   │   ├── file_utils.cpp
│   │   └── file_utils.h
│   └── config/            # 配置管理
│       ├── config.cpp
│       └── config.h
├── include/               # 公共头文件
├── tests/                 # 测试代码
├── docs/                  # 文档
├── examples/              # 示例配置文件
│   └── mapping.json
├── build/                 # 编译输出目录（不提交到 git）
├── Makefile              # Make 构建脚本
├── CMakeLists.txt        # CMake 构建脚本（可选）
├── .gitignore            # Git 忽略文件
├── README.md             # 项目说明
├── Guidance.md           # 本开发指南
└── LICENSE               # 许可证
```

### 2.3 第一阶段：最小可运行版本（MVP）

#### 步骤 1：创建主程序框架

**文件：`src/main.cpp`**
```cpp
#include <iostream>
#include <string>

using namespace std;

void printWelcome() {
    cout << "\n";
    cout << "======================================\n";
    cout << "  CipherX - Text Encryption Tool     \n";
    cout << "  Version 0.1.0                      \n";
    cout << "======================================\n";
    cout << "\n";
    cout << "Type 'help' for available commands\n";
    cout << "\n";
}

void printHelp() {
    cout << "Available commands:\n";
    cout << "  help              Show this help message\n";
    cout << "  encrypt <text>    Encrypt a string (Caesar cipher)\n";
    cout << "  decrypt <text>    Decrypt a string (Caesar cipher)\n";
    cout << "  exit              Exit the program\n";
}

int main() {
    printWelcome();
    
    string command;
    
    while (true) {
        cout << "cipherx> ";
        getline(cin, command);
        
        if (command.empty()) {
            continue;
        }
        
        if (command == "help") {
            printHelp();
        } else if (command == "exit" || command == "quit") {
            cout << "Goodbye!\n";
            break;
        } else {
            cout << "Unknown command. Type 'help' for available commands.\n";
        }
    }
    
    return 0;
}
```

**编译和运行**：
```bash
# 编译
g++ -o cipherx src/main.cpp

# 运行
./cipherx  # Linux/macOS
cipherx.exe  # Windows
```

#### 步骤 2：实现命令解析器

**文件：`src/utils/string_utils.h`**
```cpp
#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string>
#include <vector>

// 分割字符串
std::vector<std::string> split(const std::string& str, char delimiter = ' ');

// 去除字符串首尾空格
std::string trim(const std::string& str);

#endif
```

**文件：`src/utils/string_utils.cpp`**
```cpp
#include "string_utils.h"
#include <sstream>
#include <algorithm>

std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    
    while (std::getline(tokenStream, token, delimiter)) {
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }
    
    return tokens;
}

std::string trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\n\r");
    if (start == std::string::npos) {
        return "";
    }
    
    size_t end = str.find_last_not_of(" \t\n\r");
    return str.substr(start, end - start + 1);
}
```

#### 步骤 3：实现第一个加密算法（凯撒密码）

**文件：`src/cipher/caesar.h`**
```cpp
#ifndef CAESAR_H
#define CAESAR_H

#include <string>

class Caesar {
public:
    // 加密函数
    static std::string encrypt(const std::string& text, int shift);
    
    // 解密函数
    static std::string decrypt(const std::string& text, int shift);
    
private:
    // 对单个字符进行位移
    static char shiftChar(char c, int shift);
};

#endif
```

**文件：`src/cipher/caesar.cpp`**
```cpp
#include "caesar.h"

std::string Caesar::encrypt(const std::string& text, int shift) {
    std::string result = text;
    
    for (size_t i = 0; i < result.length(); i++) {
        result[i] = shiftChar(result[i], shift);
    }
    
    return result;
}

std::string Caesar::decrypt(const std::string& text, int shift) {
    // 解密就是反向位移
    return encrypt(text, -shift);
}

char Caesar::shiftChar(char c, int shift) {
    // 处理大写字母 A-Z
    if (c >= 'A' && c <= 'Z') {
        return 'A' + (c - 'A' + shift + 26) % 26;
    }
    // 处理小写字母 a-z
    else if (c >= 'a' && c <= 'z') {
        return 'a' + (c - 'a' + shift + 26) % 26;
    }
    // 其他字符不变
    else {
        return c;
    }
}
```

#### 步骤 4：集成加密功能到主程序

更新 `src/main.cpp`，添加对 encrypt 和 decrypt 命令的支持：

```cpp
#include <iostream>
#include <string>
#include <sstream>
#include "cipher/caesar.h"
#include "utils/string_utils.h"

// ... (保留之前的函数)

int main() {
    printWelcome();
    
    string command;
    int defaultShift = 3;  // 默认位移量
    
    while (true) {
        cout << "cipherx> ";
        getline(cin, command);
        
        if (command.empty()) {
            continue;
        }
        
        vector<string> tokens = split(command, ' ');
        
        if (tokens[0] == "help") {
            printHelp();
        } 
        else if (tokens[0] == "encrypt") {
            if (tokens.size() < 2) {
                cout << "Usage: encrypt <text> [shift]\n";
                continue;
            }
            
            // 获取要加密的文本（可能包含空格）
            size_t textStart = command.find(tokens[1]);
            string text = command.substr(textStart);
            
            string encrypted = Caesar::encrypt(text, defaultShift);
            cout << "Encrypted: " << encrypted << "\n";
        }
        else if (tokens[0] == "decrypt") {
            if (tokens.size() < 2) {
                cout << "Usage: decrypt <text> [shift]\n";
                continue;
            }
            
            size_t textStart = command.find(tokens[1]);
            string text = command.substr(textStart);
            
            string decrypted = Caesar::decrypt(text, defaultShift);
            cout << "Decrypted: " << decrypted << "\n";
        }
        else if (tokens[0] == "exit" || tokens[0] == "quit") {
            cout << "Goodbye!\n";
            break;
        }
        else {
            cout << "Unknown command. Type 'help' for available commands.\n";
        }
    }
    
    return 0;
}
```

#### 步骤 5：使用 Makefile 简化编译

**文件：`Makefile`**
```makefile
# 编译器
CXX = g++

# 编译选项
CXXFLAGS = -std=c++11 -Wall -Wextra -I./src

# 目标可执行文件
TARGET = cipherx

# 源文件
SOURCES = src/main.cpp \
          src/cipher/caesar.cpp \
          src/utils/string_utils.cpp

# 对象文件
OBJECTS = $(SOURCES:.cpp=.o)

# 默认目标
all: $(TARGET)

# 链接生成可执行文件
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# 编译源文件
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清理编译产物
clean:
	rm -f $(OBJECTS) $(TARGET)
	rm -f cipherx.exe  # Windows

# 安装到系统（可选）
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

.PHONY: all clean install
```

**使用方法**：
```bash
# 编译
make

# 清理
make clean

# 重新编译
make clean && make

# 安装到系统（Linux/macOS，需要 sudo）
sudo make install
```

### 2.4 第二阶段：添加更多加密算法

按照相同的模式，实现其他加密算法：

1. 在 `src/cipher/` 目录下创建对应的 `.h` 和 `.cpp` 文件
2. 实现 `encrypt` 和 `decrypt` 函数
3. 在主程序中添加新的命令处理逻辑
4. 更新 Makefile 添加新的源文件

**示例：替换密码（Substitution Cipher）**

需要支持 JSON 配置文件，可以使用简单的 JSON 解析库，推荐初学者使用：
- **nlohmann/json**：单头文件，易于集成
- 下载地址：https://github.com/nlohmann/json

### 2.5 第三阶段：完善功能

#### 文件操作

**文件：`src/utils/file_utils.h`**
```cpp
#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <string>

class FileUtils {
public:
    // 读取文件内容
    static std::string readFile(const std::string& filename);
    
    // 写入文件内容
    static bool writeFile(const std::string& filename, const std::string& content);
    
    // 检查文件是否存在
    static bool fileExists(const std::string& filename);
};

#endif
```

#### 配置管理

支持从 JSON 文件加载字符映射表等配置。

#### 命令历史

在 Windows 平台可以使用 `conio.h`，Linux/macOS 可以使用 `readline` 库或自己实现简单的历史记录。

### 2.6 跨平台编译技巧

#### 处理不同操作系统的差异

```cpp
#ifdef _WIN32
    // Windows 特定代码
    #include <windows.h>
    #define CLEAR_SCREEN "cls"
#else
    // Linux/macOS 特定代码
    #include <unistd.h>
    #define CLEAR_SCREEN "clear"
#endif
```

#### 使用 CMake（推荐，比 Makefile 更跨平台）

**文件：`CMakeLists.txt`**
```cmake
cmake_minimum_required(VERSION 3.10)
project(CipherX VERSION 0.1.0)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 包含目录
include_directories(${PROJECT_SOURCE_DIR}/src)

# 源文件
set(SOURCES
    src/main.cpp
    src/cipher/caesar.cpp
    src/utils/string_utils.cpp
)

# 可执行文件
add_executable(cipherx ${SOURCES})

# Windows 下不显示控制台窗口（可选）
# if(WIN32)
#     set_target_properties(cipherx PROPERTIES WIN32_EXECUTABLE TRUE)
# endif()
```

**编译步骤**：
```bash
# 创建构建目录
mkdir build
cd build

# 生成构建文件
cmake ..

# 编译
cmake --build .

# 或者使用 make（Linux/macOS）
make
```

---

## 三、开发过程中可能遇到的问题及解决方案

### 3.1 编译和链接问题

#### 问题 1：找不到头文件
**错误信息**：`fatal error: xxx.h: No such file or directory`

**解决方案**：
- 检查 `#include` 路径是否正确
- 确保编译时使用了 `-I` 选项指定包含目录
- 在 Makefile 中正确设置 `CXXFLAGS`

#### 问题 2：链接错误
**错误信息**：`undefined reference to 'xxx'`

**解决方案**：
- 确保所有 `.cpp` 文件都被编译并链接
- 检查 Makefile 中的 `SOURCES` 列表
- 检查函数声明和定义是否一致

#### 问题 3：Windows 和 Linux 换行符不一致
**解决方案**：
- 使用 Git 配置自动转换：
  ```bash
  git config --global core.autocrlf true  # Windows
  git config --global core.autocrlf input  # Linux/macOS
  ```

### 3.2 用户使用问题

#### 问题 1：用户需要安装编译环境吗？

**答案**：不需要！

**解决方案 - 分发预编译的二进制文件**：

1. **为每个平台编译独立的可执行文件**
   - Windows: `cipherx.exe`
   - Linux: `cipherx` (ELF binary)
   - macOS: `cipherx` (Mach-O binary)

2. **使用静态链接（重要！）**
   
   在编译时添加静态链接选项，这样可执行文件不依赖系统库：
   
   ```bash
   # Linux 静态编译
   g++ -static -o cipherx src/*.cpp
   
   # Windows (MinGW)
   g++ -static-libgcc -static-libstdc++ -o cipherx.exe src/*.cpp
   ```
   
   **注意**：完全静态编译可能导致文件较大，但用户可以直接运行。

3. **GitHub Releases 发布**
   
   在 GitHub 仓库创建 Release，上传不同平台的可执行文件：
   
   ```
   cipherx-v0.1.0-windows-x64.exe
   cipherx-v0.1.0-linux-x64
   cipherx-v0.1.0-macos-x64
   ```

4. **提供安装脚本（可选）**
   
   **Windows (`install.bat`)**:
   ```batch
   @echo off
   copy cipherx.exe C:\Windows\System32\
   echo CipherX installed successfully!
   pause
   ```
   
   **Linux/macOS (`install.sh`)**:
   ```bash
   #!/bin/bash
   sudo cp cipherx /usr/local/bin/
   sudo chmod +x /usr/local/bin/cipherx
   echo "CipherX installed successfully!"
   ```

#### 问题 2：如何让用户方便地添加到环境变量？

**Windows 方案**：
1. 手动方式：将 `cipherx.exe` 复制到 `C:\Windows\System32\`
2. 推荐方式：创建专用目录
   ```
   C:\Program Files\CipherX\cipherx.exe
   ```
   然后添加到 PATH：
   - 右键"此电脑" → 属性 → 高级系统设置 → 环境变量
   - 在"系统变量"中找到 `Path`，点击编辑
   - 添加 `C:\Program Files\CipherX\`

**Linux/macOS 方案**：
1. 复制到 `/usr/local/bin/`（推荐）
   ```bash
   sudo cp cipherx /usr/local/bin/
   sudo chmod +x /usr/local/bin/cipherx
   ```

2. 或添加到用户目录
   ```bash
   mkdir -p ~/.local/bin
   cp cipherx ~/.local/bin/
   echo 'export PATH="$HOME/.local/bin:$PATH"' >> ~/.bashrc
   source ~/.bashrc
   ```

#### 问题 3：跨平台兼容性问题

**常见问题**：
- 文件路径分隔符不同（Windows 用 `\`，Linux/macOS 用 `/`）
- 控制台编码不同（中文显示问题）

**解决方案**：

1. **统一使用 `/` 作为路径分隔符**
   C++ 标准库会自动处理

2. **处理中文编码**
   
   Windows 控制台默认使用 GBK，可以在程序开始时设置：
   ```cpp
   #ifdef _WIN32
   #include <windows.h>
   
   void setupConsole() {
       // 设置控制台代码页为 UTF-8
       SetConsoleOutputCP(CP_UTF8);
       SetConsoleCP(CP_UTF8);
   }
   #endif
   ```

### 3.3 依赖管理问题

#### 问题：如何管理第三方库？

**方案 1：单头文件库（推荐初学者）**
- 使用 nlohmann/json 这样的单头文件库
- 直接将 `.h` 文件复制到项目中
- 不需要额外编译和链接

**方案 2：包管理器**
- **vcpkg**（微软开发，跨平台）
  ```bash
  # 安装 vcpkg
  git clone https://github.com/Microsoft/vcpkg.git
  cd vcpkg
  ./bootstrap-vcpkg.sh  # Linux/macOS
  .\bootstrap-vcpkg.bat  # Windows
  
  # 安装库
  ./vcpkg install nlohmann-json
  ```

- **Conan**（Python 编写，跨平台）

### 3.4 调试技巧

#### 使用 GDB（Linux/macOS）
```bash
# 编译时添加调试信息
g++ -g -o cipherx src/*.cpp

# 使用 gdb 调试
gdb ./cipherx

# GDB 基本命令
(gdb) run              # 运行程序
(gdb) break main       # 在 main 函数设置断点
(gdb) next             # 单步执行（不进入函数）
(gdb) step             # 单步执行（进入函数）
(gdb) print variable   # 打印变量值
(gdb) continue         # 继续运行
(gdb) quit             # 退出
```

#### 使用 Visual Studio（Windows）
1. 用 Visual Studio 打开项目
2. 设置断点（点击行号左侧）
3. 按 F5 开始调试
4. 使用"监视"窗口查看变量值

#### 打印调试
```cpp
#include <iostream>

#ifdef DEBUG
#define LOG(x) std::cout << "[DEBUG] " << x << std::endl
#else
#define LOG(x)
#endif

// 使用
LOG("Variable value: " << myVar);
```

编译时添加 `-DDEBUG` 启用调试输出。

### 3.5 性能优化

#### 第一版不需要过度优化
- 代码清晰可读比性能更重要
- 先确保功能正确，再考虑优化

#### 基本优化原则
1. **避免不必要的字符串拷贝**
   ```cpp
   // 不好
   void process(std::string str) { }
   
   // 好
   void process(const std::string& str) { }
   ```

2. **使用合适的数据结构**
   - 频繁查找：使用 `std::map` 或 `std::unordered_map`
   - 顺序遍历：使用 `std::vector`

3. **预分配内存**
   ```cpp
   std::string result;
   result.reserve(text.length());  // 预分配空间
   ```

---

## 四、开发流程建议

### 4.1 迭代式开发

**版本 0.1.0**：基本框架 + 凯撒密码
- 实现 CLI 交互框架
- 实现凯撒密码加密/解密
- 编写基本文档

**版本 0.2.0**：添加更多算法
- 实现替换密码
- 实现维吉尼亚密码
- 支持 JSON 配置文件

**版本 0.3.0**：文件操作
- 支持从文件读取文本
- 支持保存结果到文件

**版本 0.4.0**：用户体验优化
- 命令历史记录
- Tab 自动补全
- 更友好的错误提示

**版本 1.0.0**：正式发布
- 完善文档
- 多平台测试
- 发布二进制文件

### 4.2 版本控制（Git）

```bash
# 初始化仓库
git init

# 添加 .gitignore
echo "build/" >> .gitignore
echo "*.o" >> .gitignore
echo "*.exe" >> .gitignore
echo "cipherx" >> .gitignore

# 提交代码
git add .
git commit -m "Initial commit: project structure"

# 创建开发分支
git checkout -b develop

# 功能完成后合并到主分支
git checkout main
git merge develop

# 打标签
git tag -a v0.1.0 -m "Version 0.1.0: Basic Caesar cipher"
```

### 4.3 测试建议

#### 手动测试
创建测试用例文档，每次修改后逐一测试：

```
测试用例 1：加密英文
输入：encrypt "Hello World"
期望输出：Khoor Zruog

测试用例 2：解密
输入：decrypt "Khoor Zruog"
期望输出：Hello World

测试用例 3：中文字符
输入：encrypt "你好世界"
期望输出：你好世界（保持不变）
```

#### 自动化测试（进阶）
可以使用 Google Test 框架，但初学者可以先专注于功能实现。

---

## 五、示例配置文件

### 5.1 字符映射表（mapping.json）

```json
{
  "name": "Custom Substitution Cipher",
  "description": "A custom character mapping",
  "mapping": {
    "a": "z",
    "b": "y",
    "c": "x",
    "d": "w",
    "e": "v",
    "f": "u",
    "g": "t",
    "h": "s",
    "i": "r",
    "j": "q",
    "k": "p",
    "l": "o",
    "m": "n",
    "n": "m",
    "o": "l",
    "p": "k",
    "q": "j",
    "r": "i",
    "s": "h",
    "t": "g",
    "u": "f",
    "v": "e",
    "w": "d",
    "x": "c",
    "y": "b",
    "z": "a"
  }
}
```

---

## 六、常见问题（FAQ）

### Q1: 我应该用 C 还是 C++？
**A**: 推荐使用 C++。C++ 的 `std::string` 和 STL 容器能大大简化开发，比 C 的字符数组更安全易用。

### Q2: 需要使用面向对象编程吗？
**A**: 第一版可以不用。使用简单的函数和命名空间即可。随着项目复杂度增加，可以逐步引入类和对象。

### Q3: 如何确保代码质量？
**A**: 
- 编写清晰的注释
- 使用有意义的变量名
- 保持函数简短（每个函数只做一件事）
- 多测试，包括边界情况

### Q4: 项目可以用多久完成？
**A**: 
- 基础版（凯撒密码）：1-2 天
- 添加 3-4 种算法：3-5 天
- 完善功能和文档：1-2 周

### Q5: 学习资源推荐？
**A**: 
- **C++ 入门**：《C++ Primer》
- **命令行工具开发**：参考其他 CLI 工具源码（如 `git`，`curl`）
- **加密算法**：维基百科，《图解密码技术》
- **项目管理**：GitHub 官方文档

---

## 七、下一步行动

1. **立即开始**
   - 创建项目目录结构
   - 编写最小可运行版本
   - 提交到 GitHub

2. **第一周目标**
   - 实现 CLI 交互框架
   - 实现凯撒密码
   - 编写 README

3. **第一个月目标**
   - 实现 3-5 种加密算法
   - 支持文件操作
   - 发布 v0.1.0

4. **长期规划**
   - 收集用户反馈
   - 持续添加新功能
   - 优化性能和用户体验

---

## 八、附录

### 8.1 推荐的代码风格

```cpp
// 文件头注释
/**
 * @file caesar.cpp
 * @brief Implementation of Caesar cipher
 * @author Your Name
 * @date 2024-01-01
 */

// 函数注释
/**
 * @brief Encrypt text using Caesar cipher
 * @param text The text to encrypt
 * @param shift The shift amount
 * @return Encrypted text
 */
std::string Caesar::encrypt(const std::string& text, int shift) {
    // 实现...
}
```

### 8.2 有用的命令行参数解析

如果需要支持类似 `cipherx encrypt -f input.txt -o output.txt` 的命令行参数：

```cpp
// 简单的参数解析示例
int main(int argc, char* argv[]) {
    if (argc > 1) {
        // 命令行模式
        std::string command = argv[1];
        if (command == "encrypt" && argc >= 3) {
            std::string text = argv[2];
            // 处理加密...
        }
    } else {
        // 交互模式
        // 进入 REPL...
    }
}
```

### 8.3 README 模板

```markdown
# CipherX

一个交互式命令行加密/解密工具。

## 特性

- 支持多种加密算法
- 交互式命令行界面
- 跨平台支持（Windows/Linux/macOS）

## 安装

### 从源码编译

\`\`\`bash
git clone https://github.com/yourusername/cipherx.git
cd cipherx
make
\`\`\`

### 下载预编译版本

从 [Releases](https://github.com/yourusername/cipherx/releases) 下载对应平台的版本。

## 使用方法

\`\`\`bash
$ cipherx
cipherx> help
cipherx> encrypt "Hello World"
\`\`\`

## 许可证

MIT License
```

---

## 总结

这份指南为你提供了从零开始开发 CipherX CLI 工具的完整路线图。记住：

1. **从简单开始**：先实现一个可运行的最小版本
2. **迭代开发**：逐步添加功能，不要一次做太多
3. **重视文档**：良好的文档让项目更容易维护
4. **多测试**：每次修改后都要测试
5. **持续学习**：遇到问题多查资料，多参考优秀项目

祝你开发顺利！如有问题，欢迎随时查阅本指南。

---

**文档版本**：1.0
**最后更新**：2024-01-01
**维护者**：SmlCoke
