//
// Created by 沈嘉瑞 on 2023.10.15.
//

#ifndef SIMPLE_CALCULATOR_LINKSTACK_H
#define SIMPLE_CALCULATOR_LINKSTACK_H
#include "Tool.h"

template<class T>
struct LinkStackNode{
    T data;
    LinkStackNode* next;
    LinkStackNode(): next(nullptr){};
    LinkStackNode(T d): data(d), next(nullptr){};
};

template<class T>
class LinkStack {
public:
    LinkStack();
    ~LinkStack();

    bool empty();
    void push(T);
    T pop();
    T getTop();
    int size();
    //void clear();无需实现的清空函数
    //T peek();无需实现的查看函数
private:
    LinkStackNode<T>* head;
};

//构造函数
template<class T>
LinkStack<T>::LinkStack() {
    head = new LinkStackNode<T>;
}

//析构函数
template<class T>
LinkStack<T>::~LinkStack() {
    if (head->next == nullptr){
        delete head;
        return;
    } else{
        LinkStackNode<T>* curr = head;
        LinkStackNode<T>* now = head;
        while (curr->next != nullptr){
            now = curr;
            curr = curr->next;
            delete now;
        }
        delete curr;
    }
    head = nullptr;
}

//栈是否空
template<class T>
bool LinkStack<T>::empty() {
    if (head->next== nullptr){
        return true;
    } else{
        return false;
    }
}

//压入栈(头插法)
template<class T>
void LinkStack<T>::push(T e) {
    if (empty()){
        head->next = new LinkStackNode<T>(e);
    } else{
        LinkStackNode<T>* curr = new LinkStackNode<T>(e);
        curr->next = head->next;
        head->next = curr;
    }
}

//弹出栈
template<class T>
T LinkStack<T>::pop() {
    if (empty()) {
        throw StackEmptyException("栈是空的。操作失败。");
    } else if (size() == 1){
        T tmp = head->next->data;
        delete head->next;
        head->next = nullptr;
        return tmp;
    } else{
        T tmp = head->next->data;
        LinkStackNode<T>* curr = head->next;
        head->next = head->next->next;
        delete curr;
        return tmp;
    }
}

//获得栈顶
template<class T>
T LinkStack<T>::getTop() {
    if (empty()) {
        throw StackEmptyException("栈是空的。操作失败。");
    } else {
        return head->next->data;
    }
}

//数量
template<class T>
int LinkStack<T>::size() {
    int num = 0;
    if (!empty()) {
        LinkStackNode<T>* curr = head;
        while (curr->next != nullptr){
            curr = curr->next;
            num ++;
        }
    }
    return num;
}

#endif //SIMPLE_CALCULATOR_LINKSTACK_H
