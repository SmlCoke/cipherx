# cipherx
对文本进行进行多种加密-解密的交互式命令行工具。 
- 本项目作为SmlCoke开发的第一个长期维护、可被其他用户下载、在多操作系统上运行的小工具。
- 文本中包含的字符支持中文，英文以及常用的标点符号。
- 第一版工具采用C/C++实现。

## Directory Tree
```
cipherx/  
├── README.md                          # This documentation  
├── bin/                               # Compiled binaries
├── src/                               # Source code directory
│   ├── utils/                         # Utility functions
│   │   ├── string_utils.cpp
│   │   ├── string_utils.h
│   ├── cipher/                        # Cipher functions
│   │   ├── caesar.cpp
│   │   ├── caesar.h
│   └── main.cpp                       # Main Program
├── tests/                             # Unit tests
│   ├── test_string_utils.cpp
│   ├── test_caesar.cpp
├── CMakeLists.txt                     # CMake build configuration
├── Guidance.md                        # Project guidance and best practices
```
