# CipherX 🔐

![Build Status](https://github.com/SmlCoke/cipherx/actions/workflows/release.yml/badge.svg)
![License](https://img.shields.io/github/license/SmlCoke/cipherx)
![Release](https://img.shields.io/github/v/release/SmlCoke/cipherx)

**CipherX** is a cross-platform, interactive command-line tool for text encryption and decryption.

As the first long-term maintained project developed by SmlCoke, CipherX aims to provide a lightweight, fast, and easy-to-use encryption experience. Developed in C++, it supports Windows, Linux, and macOS operating systems, with full support for Chinese, English, and common punctuation marks.

## Features

- **Cross-Platform Support**: Write once, run anywhere (Windows / Linux / macOS).
- **Interactive Command-Line (REPL)**: Provides a user-friendly interactive shell.
- **Multiple Encryption Algorithms**:
  - [x] **Caesar Cipher**: Classic shift encryption.
  - [ ] **Vigenère Cipher** (In development...)
  - [ ] **Base64** (Planned...)
- **Internationalization**: Built on UTF-8 encoding, perfectly supporting Chinese character encryption.
- **Automated Build**: Automated build and release process based on CMake and GitHub Actions.

## Getting Started
 
### For Users

You do not need to install any programming environment. Simply download and run.

1. Visit the [**Releases Page**](https://github.com/SmlCoke/cipherx/releases) of this project.
2. Download the version corresponding to your operating system:
   - **Windows**: Download `cipherx-windows.exe`
   - **Linux**: Download `cipherx-linux`
   - **macOS**: Download `cipherx-macos`
3. **Run**:
   - Windows: Double-click to run or run in the terminal (Environment path must be set).
   - Linux/macOS: You may need to grant execution permissions:
     ```bash
     chmod +x cipherx-linux  # or cipherx-macos
     ./cipherx-linux
     ```

### For Developers

If you want to compile this project from source, please ensure your environment has `CMake (3.10+)` and a `C++ Compiler (GCC/Clang/MSVC)` installed.

```bash
# 1. Clone the repository
git clone https://github.com/SmlCoke/cipherx.git
cd cipherx

# 2. Create a build directory
mkdir build && cd build

# 3. Configure CMake
cmake ..

# 4. Build
cmake --build .

# 5. Run tests (Optional but recommended)
ctest

# 6. Run the program
./cipherx  # On Windows: .\Debug\cipherx.exe or .\cipherx.exe
```

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
