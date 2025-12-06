#ifndef CAESAR_H
#define CAESAR_H

#include <string>

class Caesar {
public:

    // 删除默认构造函数，明确表示这个类不应该被实例化
    Caesar() = delete; 

    // 加密函数
    static std::string encrypt(const std::string& text, int shift);
    // fj: 静态成员函数属于类本身，而不属于类的某个具体对象
    // fj: 因此，不需要创建对象（new Caesar() 或 Caesar c;），直接通过 类名::函数名 即可调用
    
    // 解密函数
    static std::string decrypt(const std::string& text, int shift);
    
private:
    // 对单个字符进行位移
    static char shiftChar(char c, int shift);
};

#endif