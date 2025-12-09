#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <limits> // 用于 numeric_limits

using namespace std;

#include "utils/string_utils.h"
#include "cipher/caesar.h"

void printWelcome(std::string version) {
    cout << "\n";
    cout << "======================================\n";
    cout << "  CipherX - Text Encryption Tool     \n";
    cout << "  Version " << version << "\n";
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
    transform(str.begin(), str.end(), str.begin(), [](unsigned char c){ 
        return std::tolower(c); 
    });
    return str;
}

int main() {

    string cipherx_version = "0.1.1";

    printWelcome(cipherx_version);
    
    string commandLine; // 变量名改为 commandLine 更贴切
    
    while (true) {
        cout << "cipherx> ";
        
        if (!getline(cin, commandLine)) {
            cout << "\nExiting...\n";
            break;
        }
        
        if (trim(commandLine).empty()) {
            continue;
        }

        // 1209: 使用智能解析，支持引号
        std::vector<std::string> cmd_tokens = parseCommandLine(commandLine);

        if (cmd_tokens.empty()) continue;

        // 1209: 只将第一个 token (命令) 转为小写进行判断
        string action = toLowerCase(cmd_tokens[0]);

        if (action == "help") {
            printHelp();
        } else if (action == "exit" || action == "quit" || action == "q") {
            cout << "Goodbye, Thank you for using cipherx project " << cipherx_version << "!\n";
            break;
        } else if (action == "version" || action == "v") {
            cout << "CipherX - Text Encryption/Decryption Tool\n";
            cout << "Version: " << cipherx_version << "\n";
            cout << "Built with C++17\n";
            cout << "Author: SmlCoke\n";
        } else if (action == "encrypt" || action == "e" || 
                   action == "decrypt" || action == "d") {
            
            if (cmd_tokens.size() < 3) {
                cout << "cipherx> Warning: usage: <command> <mode> <text>\n";
                continue;
            }

            // 1209: 获取模式并转小写
            std::string mode = toLowerCase(cmd_tokens[1]);

            // 1209: 获取文本：支持引号，也支持不加引号的贪婪匹配
            // 情况 A: e caesar "hello world" -> tokens: [e, caesar, hello world] (size=3)
            // 情况 B: e caesar hello world   -> tokens: [e, caesar, hello, world] (size=4)
            std::string text;
            if (cmd_tokens.size() == 3) {
                text = cmd_tokens[2];
            } else {
                // 如果用户没加引号，我们将第3个及之后的所有 token 拼回去，中间补空格
                for (size_t i = 2; i < cmd_tokens.size(); ++i) {
                    text += cmd_tokens[i];
                    if (i < cmd_tokens.size() - 1) text += " ";
                }
            }

            if (mode == "caesar") {
                cout << "cipherx> Please input shifter (integer): ";
                int shifter;
                // 1209: 健壮的输入处理
                if (!(cin >> shifter)) {
                    cout << "cipherx> Invalid input. Operation cancelled.\n";
                    cin.clear(); // 清除错误标志
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清空缓冲区
                    continue;
                }
                // 1209: 清除输入流中遗留的换行符，否则会跳过下一次 getline
                // 1209: 如果没有这一句，加密完成后会出现：
                // 1209: "cipherx> cipherx>"
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                std::string result;
                if (action == "encrypt" || action == "e") {
                    result = Caesar::encrypt(text, shifter);
                    cout << "cipherx> Encrypted: " << result << "\n";
                } else {
                    result = Caesar::decrypt(text, shifter);
                    cout << "cipherx> Decrypted: " << result << "\n";
                }
            } else {
                cout << "cipherx> Unknown mode: " << mode << "\n";
            }
        } else {
            cout << "cipherx> Unknown command: '" << action << "'\n";
        }
    }
    
    return 0;
}