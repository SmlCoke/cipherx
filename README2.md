# CipherX 🔐

![Build Status](https://github.com/SmlCoke/cipherx/actions/workflows/release.yml/badge.svg)
![License](https://img.shields.io/github/license/SmlCoke/cipherx)
![Release](https://img.shields.io/github/v/release/SmlCoke/cipherx)

**CipherX** 是一个跨平台的、交互式的命令行文本加密/解密工具。

作为 SmlCoke 开发的第一个长期维护项目，CipherX 旨在提供轻量、快速且易于使用的加密体验。它基于 C++ 开发，支持 Windows、Linux 和 macOS 操作系统，并完美支持中文、英文及常用标点符号的处理。

## ✨ 功能特性 (Features)

- **多平台支持**：一次编写，处处运行 (Windows / Linux / macOS)。
- **交互式命令行 (REPL)**：提供友好的交互式 Shell，支持命令补全和历史记录（计划中）。
- **多种加密算法**：
  - [x] **Caesar Cipher (凯撒密码)**：经典的位移加密。
  - [ ] **Vigenère Cipher** (开发中...)
  - [ ] **Base64** (计划中...)
- **国际化支持**：底层采用 UTF-8 编码，完美支持中文字符加密。
- **自动化构建**：基于 CMake 和 GitHub Actions 的自动化构建与发布流程。

## 🚀 快速开始 (Getting Started)

### 对于普通用户 (User)

你不需要安装任何编程环境，直接下载即可运行。

1. 访问本项目的 [**Releases 页面**](https://github.com/SmlCoke/cipherx/releases)。
2. 下载对应你操作系统的版本：
   - **Windows**: 下载 `cipherx-windows.exe`
   - **Linux**: 下载 `cipherx-linux`
   - **macOS**: 下载 `cipherx-macos`
3. **运行**：
   - Windows: 双击运行或在终端运行。
   - Linux/macOS: 可能需要赋予执行权限：
     ```bash
     chmod +x cipherx-linux  # 或 cipherx-macos
     ./cipherx-linux
     ```

### 对于开发者 (Developer)

如果你想从源码编译本项目，请确保你的环境已安装 `CMake (3.10+)` 和 `C++ 编译器 (GCC/Clang/MSVC)`。

```bash
# 1. 克隆仓库
git clone https://github.com/SmlCoke/cipherx.git
cd cipherx

# 2. 创建构建目录
mkdir build && cd build

# 3. 配置 CMake
cmake ..

# 4. 编译
cmake --build .

# 5. 运行测试 (可选但推荐)
ctest

# 6. 运行程序
./cipherx  # Windows 下是 .\Debug\cipherx.exe 或 .\cipherx.exe
```


## 📖 使用指南 (Usage)
启动程序后，你将进入交互式界面：
```bash
======================================
  CipherX - Text Encryption Tool     
  Version 0.1.0                      
======================================

Type 'help' for available commands

cipherx> 
```


## 📂 项目结构 (Directory Tree)
```bash
cipherx/  
├── README.md                          # 项目文档
├── bin/                               # 编译后的二进制文件输出目录
├── src/                               # 源代码目录
│   ├── utils/                         # 通用工具模块
│   │   ├── string_utils.cpp       # 字符串处理实现
│   │   ├── string_utils.h
│   ├── cipher/                        # 加密算法模块
│   │   ├── caesar.cpp             # 凯撒密码实现
│   │   ├── caesar.h
│   └── main.cpp                       # 程序入口与交互逻辑
├── tests/                             # 单元测试目录
│   ├── test_string_utils.cpp
│   ├── test_caesar.cpp
├── CMakeLists.txt                     # CMake 构建配置
├── .github/workflows/                 # GitHub Actions 自动化配置
└── Guidance.md                        # 开发指南
```