# CipherX 🔐

[![Build Status](https://github.com/SmlCoke/cipherx/actions/workflows/release.yml/badge.svg)](https://github.com/SmlCoke/cipherx/actions/workflows/release.yml)
[![License](https://img.shields.io/github/license/SmlCoke/cipherx)](https://github.com/SmlCoke/cipherx/blob/main/LICENSE)
[![Release](https://img.shields.io/github/v/release/SmlCoke/cipherx)](https://github.com/SmlCoke/cipherx/releases)

**CipherX** is a cross-platform, interactive command-line tool for text encryption and decryption.

As the first long-term maintained project developed by SmlCoke, CipherX aims to provide a lightweight, fast, and easy-to-use encryption experience. Developed in C++, it supports Windows, Linux, and macOS operating systems, with full support for Chinese, English, and common punctuation marks.

## Features

- **Cross-Platform Support**: Write once, run anywhere (Windows / Linux / macOS).
- **Interactive Command-Line (REPL)**: Provides a user-friendly interactive shell with command completion and history (planned).
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
   - Windows: Double-click to run or run in the terminal.
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


## Usage
After starting the program, you will enter the interactive interface:
```bash
======================================
  CipherX - Text Encryption Tool     
  Version 0.1.0                      
======================================

Type 'help' for available commands

cipherx> 
```


## Directory Tree
```bash
cipherx/  
├── README.md                          # Project documentation
├── bin/                               # Output directory for compiled binaries
├── src/                               # Source code directory
│   ├── utils/                         # Utility modules
│   │   ├── string_utils.cpp           # String processing implementation
│   │   ├── string_utils.h
│   ├── cipher/                        # Encryption algorithm modules
│   │   ├── caesar.cpp                 # Caesar cipher implementation
│   │   ├── caesar.h
│   └── main.cpp                       # Program entry and interaction logic
├── tests/                             # Unit tests directory
│   ├── test_string_utils.cpp
│   ├── test_caesar.cpp
├── CMakeLists.txt                     # CMake build configuration
├── .github/workflows/                 # GitHub Actions automation configuration
└──
```