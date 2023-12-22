//
// Created by 沈嘉瑞 on 2023.11.02.
//

#include "Tool.h"
double inputDouble(){
    return doubleNumberTest(inputString());
}

int inputInt(){
    return intNumberTest(inputString());
}

string inputString(){
    string tmp;
    cin>>tmp;
    exitTest(tmp);
    return tmp;
}

char inputOneChar(){
    return inputString()[0];
}

char inputOneLargeChar(){
    return LargeCharTest(inputOneChar());
}

bool isTreeOP(char c){
    return (c=='(' || c==')' || c==',');
}

char LargeCharTest(char c){
    if (isLargeChar(c)){
        return c;
    } else{
        throw CharException("输入的不是大写字母人员，操作失败。");
    }
}

bool isLargeChar(char c){
    return (c>='A' && c<='Z');
}

//double转换
double doubleNumberTest(string num){
    double tempDouble = 0;
    std::istringstream iss(num);
    if (iss >> tempDouble) {
        return tempDouble;
    } else {
        throw NumberException("在需要输入小数的地方输入的不是一个数字，操作失败！");
    }
};

int intNumberTest(string num){
    int tempDouble = 0;
    std::istringstream iss(num);
    if (iss >> tempDouble) {
        return tempDouble;
    } else {
        throw NumberException("在需要输入整数的地方输入的不是一个数字，操作失败！");
    }
}

void exitTest(string s){
    if (s == "q"){
        throw ExitException("已手动退出进程。");
    }
}