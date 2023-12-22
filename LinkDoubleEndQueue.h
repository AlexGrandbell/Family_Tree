//
// Created by 沈嘉瑞 on 2023.10.16.
//

#ifndef HOSPITAL_QUEUING_SYSTEM_LINKQUEUE_H
#define HOSPITAL_QUEUING_SYSTEM_LINKQUEUE_H
#include "Tool.h"

//链式队列实定义
//注意，这是一个双端队列，可以从两端插入，一端输出
template<class T>
struct LinkDoubleEndQueueNode{
    T data;
    LinkDoubleEndQueueNode* next;
    LinkDoubleEndQueueNode(): next(nullptr){};
    LinkDoubleEndQueueNode(T d): data(d), next(nullptr){}
};

template<class T>
class LinkDoubleEndQueue {
private:
    LinkDoubleEndQueueNode<T>* front;
    LinkDoubleEndQueueNode<T>* rear;
public:
    LinkDoubleEndQueue();
    ~LinkDoubleEndQueue();
    bool empty();
    void push(T);
    void pushFromOtherSide(T);
    T pop();
    T getTail();
    int size();
};

//构造函数
template<class T>
LinkDoubleEndQueue<T>::LinkDoubleEndQueue() {
    front = new LinkDoubleEndQueueNode<T>;
    rear = front;
}

//析构函数
template<class T>
LinkDoubleEndQueue<T>::~LinkDoubleEndQueue(){
    if (front->next == nullptr){
        delete front;
        return;
    } else{
        LinkDoubleEndQueueNode<T>* curr = front;
        LinkDoubleEndQueueNode<T>* now = front;
        while (curr->next != nullptr){
            now = curr;
            curr = curr->next;
            delete now;
        }
        delete curr;
    }
    front = nullptr;
}

//是否为空
template<class T>
bool LinkDoubleEndQueue<T>::empty() {
    if (front->next== nullptr){
        return true;
    } else{
        return false;
    }
}

//入队函数
template<class T>
void LinkDoubleEndQueue<T>::push(T e) {
    rear->next = new LinkDoubleEndQueueNode(e);
    rear = rear->next;
}

//另一端优先入队函数
template<class T>
void LinkDoubleEndQueue<T>::pushFromOtherSide(T e) {
    LinkDoubleEndQueueNode<T>* p = new LinkDoubleEndQueueNode(e);
    if (empty()){
        push(e);
    } else{
        p->next = front->next;
        front->next = p;
    }
}

//出队函数
template<class T>
T LinkDoubleEndQueue<T>::pop() {
    if (empty()) {
        throw QueueEmptyException("队是空的。操作失败。");
    } else if (size() == 1){
        T tmp = front->next->data;
        delete front->next;
        front->next = nullptr;
        rear = front;
        return tmp;
    } else{
        T tmp = front->next->data;
        LinkDoubleEndQueueNode<T>* curr = front->next;
        front->next = front->next->next;
        delete curr;
        return tmp;
    }
}

//得到队尾(即将出队的)
template<class T>
T LinkDoubleEndQueue<T>::getTail() {
    if (empty()) {
        throw QueueEmptyException("栈是空的。操作失败。");
    } else {
        return front->next->data;
    }
}

//数量
template<class T>
int LinkDoubleEndQueue<T>::size() {
    int num = 0;
    if (!empty()) {
        LinkDoubleEndQueueNode<T>* curr = front;
        while (curr->next != nullptr){
            curr = curr->next;
            num ++;
        }
    }
    return num;
}

#endif //HOSPITAL_QUEUING_SYSTEM_LINKQUEUE_H
