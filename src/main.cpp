#include <iostream>
#include <string>
#include <algorithm> // 用于 transform

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
    cout << "  help            Show this help message\n";
    cout << "  exit / quit     Exit the program\n";
}

// 辅助函数：将字符串转换为小写
string toLowerCase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
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
        
        if (command == "help") {
            printHelp();
        } else if (command == "exit" || 
                   command == "quit" ||
                   command == "e" ||
                   command == "q") {
            cout << "Goodbye, Thank you for using cipherx project " << cipherx_version << "!\n";
            break;
        } else {
            cout << "Unknown command: '" << command << "'\n";
            cout << "Type 'help' for available commands.\n";
        }
    }
    
    return 0;
}