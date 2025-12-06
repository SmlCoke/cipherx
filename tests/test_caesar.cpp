#include <iostream>
#include <cassert>
#include "../src/cipher/caesar.h"

int main() {
    // 测试加密
    std::string plaintext = "Hello, World!";
    int shift = 3;
    std::string ciphertext = Caesar::encrypt(plaintext, shift);
    std::cout << "Encrypted: " << ciphertext << std::endl;

    // 测试解密
    std::string decrypted = Caesar::decrypt(ciphertext, shift);
    std::cout << "Decrypted: " << decrypted << std::endl;

    // 确保解密后的文本与原文相同
    assert(decrypted == plaintext);

    std::cout << "All tests passed!" << std::endl;
    return 0;
}