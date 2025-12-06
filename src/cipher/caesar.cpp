#include "caesar.h"

std::string Caesar::encrypt(const std::string& text, int shift) {
    std::string result = text;
    
    for (size_t i = 0; i < result.length(); i++) {
        result[i] = shiftChar(result[i], shift);
    }
    
    return result;
}

std::string Caesar::decrypt(const std::string& text, int shift) {
    // 解密就是反向位移
    return encrypt(text, -shift);
}

char Caesar::shiftChar(char c, int shift) {
    // fj: 规范化 shift，确保它在 [0, 25] 范围内
    // fj: 这一步非常关键，解决了负数位移的问题
    int normalizedShift = (shift % 26 + 26) % 26;
    // fj: 如果没有这一步，直接实现时，会出现： ('B' - 'A' - 3)%26 = -4, 导致 'A' - 4 跃出字母范围
    // 处理大写字母 A-Z
    if (c >= 'A' && c <= 'Z') {
        return 'A' + (c - 'A' + normalizedShift) % 26;
    }
    // 处理小写字母 a-z
    else if (c >= 'a' && c <= 'z') {
        return 'a' + (c - 'a' + normalizedShift) % 26;
    }
    // 其他字符不变
    else {
        return c;
    }
}