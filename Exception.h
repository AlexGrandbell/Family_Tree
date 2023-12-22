//
// Created by 沈嘉瑞 on 2023.11.02.
//

#ifndef FAMILY_TREE_EXCEPTION_H
#define FAMILY_TREE_EXCEPTION_H
#include <stdexcept> // 包含stdexcept头文件以使用标准异常类
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <stack>
using namespace std;

//异常父类
class MyException:public exception{
public:
    explicit MyException(const char* message):errorMessage(message){}
    const char * what() const noexcept override{
        return errorMessage.c_str();
    }
private:
    string errorMessage;
};

//输入树格式异常
class inputException:public MyException{
public:
    explicit inputException(const char* message): MyException(message){}
};

//手动退出
class ExitException:public MyException{
public:
    ExitException(const char* message): MyException(message){}
};

//数字输入字符异常
class NumberException:public MyException{
public:
    NumberException(const char* message): MyException(message){}
};

//输入字符异常
class CharException:public MyException{
public:
    CharException(const char* message): MyException(message){}
};

//树空异常
class TreeEmptyException:public MyException{
public:
    TreeEmptyException(const char* message): MyException(message){}
};

//表达式未初始化异常
class ExpressEmptyException: public MyException{
public:
    ExpressEmptyException(const char* message): MyException(message){}
};

//成员不存在异常
class InExistenceException: public MyException{
public:
    InExistenceException(const char* message): MyException(message){}
};

//栈空异常
class StackEmptyException:public MyException{
public:
    StackEmptyException(const char* message): MyException(message){}
};

//多根异常
class RootException:public MyException{
public:
    RootException(const char* message): MyException(message){}
};

//队空异常
class QueueEmptyException:public MyException{
public:
    QueueEmptyException(const char* message): MyException(message){}
};
#endif //FAMILY_TREE_EXCEPTION_H
