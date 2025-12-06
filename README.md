# cipherx
An interactive command-line tool for multiple encryption and decryption of text.  
- This project is the first long-term maintained, downloadable, and cross-platform utility developed by SmlCoke.  
- The text supports Chinese, English, and common punctuation marks.  
- The first version of the tool is implemented in C/C++.

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
