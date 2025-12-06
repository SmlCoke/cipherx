#include <iostream>
#include <string>
#include <algorithm> // 用于 transform
#include <vector>
using namespace std;

#include "utils/string_utils.h"
#include "cipher/caesar.h"
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
    cout << "  help                         Show this help message\n";
    cout << "  exit / quit                  Exit the program\n";
    cout << "  version                      Show the version information\n";
    cout << "  encrypt / e <mode> <text>    Encrypt a text\n";
    cout << "  decrypt / d <mode> <text>    Decrypt a text\n";
}

// 辅助函数：将字符串转换为小写
string toLowerCase(string str) {
    // [修改] 使用 lambda 表达式并强制转换为 unsigned char，这是 C++ 标准推荐的安全做法
    transform(str.begin(), str.end(), str.begin(), [](unsigned char c){ 
        return std::tolower(c); 
    });
    return str;
}

int main() {
    printWelcome();
    
    string command;
    string cipherx_version = "0.1.0";

    while (true) {
        cout << "cipherx> ";
        
        // 检查输入流状态，处理 Ctrl+D/Ctrl+Z
        if (!getline(cin, command)) {
            cout << "\nExiting...\n";
            break;
        }
        
        if (command.empty()) {
            continue;
        }

        // 将命令转换为小写以便比较
        command = toLowerCase(command);

        std::vector<std::string> cmd_tokens = split(command, ' ');

        if (cmd_tokens[0] == "help") {
            printHelp();
        } else if (command == "exit" || 
                   command == "quit" ||
                   command == "q") {
            cout << "Goodbye, Thank you for using cipherx project " << cipherx_version << "!\n";
            break;
        } else if (command == "version" ||
                   command == "v") {
            cout << "CipherX - Text Encryption/Decryption Tool\n";
            cout << "Version: " << cipherx_version << "\n";
            cout << "Built with C++17\n";
            cout << "Author: SmlCoke\n";
        } else if (cmd_tokens[0] == "encrypt" || cmd_tokens[0] == "e") {
            if (cmd_tokens.size() < 3) {
                cout << "cipherx> Warning: encrypt usage: encrypt/e <mode> <text>\n";
                continue;
            }
            std::string mode = cmd_tokens[1];
            std::string text = cmd_tokens[2];

            if (mode == "caesar") {
                cout << "cipherx> Please input encryption shifter: ";
                int shifter;
                cin >> shifter;
                std::string encrypted = Caesar::encrypt(text, shifter);
                cout << "cipherx> Encrypted text (Caesar): " << encrypted << "\n";
            } else {
                cout << "cipherx> Unknown encryption mode: " << mode << "\n";
            }
        } else if (cmd_tokens[0] == "decrypt" || cmd_tokens[0] == "d") {
            if (cmd_tokens.size() < 3) {
                cout << "cipherx> Warning: decrypt usage: decrypt/d <mode> <text>\n";
                continue;
            }
            std::string mode = cmd_tokens[1];
            std::string text = cmd_tokens[2];

            if (mode == "caesar") {
                cout << "cipherx> Please input decryption shifter: ";
                int shifter;
                cin >> shifter;
                std::string decrypted = Caesar::decrypt(text, shifter);
                cout << "cipherx> Decrypted text (Caesar): " << decrypted << "\n";
            } else {
                cout << "cipherx> Unknown decryption mode: " << mode << "\n";
            }
        } else {
            cout << "cipherx> Unknown command: '" << command << "'\n";
            cout << "cipherx> Type 'help' for available commands.\n";
        }
    }
    
    return 0;
}