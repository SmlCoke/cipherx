# CipherX Development Log

## Overview
This document serves as a log for the development of the CipherX project, detailing key decisions, changes, and progress throughout the project lifecycle.

## 11.25 Nov. 2025
The CMakeLists.txt and c_cpp_properties.json file for C/C++ development has been configured.

## 12.05 Dec. 2025
1. Basic interactive command-line interface development successful.
2. String_utils.cpp has passed all tests.
   1. Test method `CTest`: when some tests fail, `assert` will terminate the program and print an error message. Then this program return a code `1`, that can't be accepted by CMake `CTest`
   2. To ensure Chinese characters are handled correctly, the console encoding has been set to UTF-8.
   3. To ensure **ii** can be completed in different OS such as Linux and Windows, detailed configuration can be seen in [`src/utils/string_utils.cpp`](src/utils/string_utils.cpp)