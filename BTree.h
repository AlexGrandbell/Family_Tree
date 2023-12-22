//
// Created by 沈嘉瑞 on 2023.11.02.
//

#ifndef FAMILY_TREE_BTREE_H
#define FAMILY_TREE_BTREE_H
#include "LinkStack.h"
#include "LinkDoubleEndQueue.h"

template<class T>
struct BTreeNode{
    T data;
    BTreeNode* lTree;
    BTreeNode* rTree;
    BTreeNode():lTree(nullptr),rTree(nullptr){};
    BTreeNode(T d):data(d),lTree(nullptr),rTree(nullptr){};
};

template<class T>
class BTree{
public:
    BTree();
    BTree(string);//根据表达式初始化树
    ~BTree();

    void checkBTreeString(string);

    void buildTree(string);//根据括号表达式构建树

    void NLRRecursionShow();//先序递归算法输出
    void NLRNoneRecursionShow();//先序非递归算法输出
    void LNRRecursionShow();//中序递归算法输出
    void LNRNoneRecursionShow();//中序非递归算法输出
    void LRNRecursionShow();//后序递归算法
    void LRNNoneRecursionShow();//后序非递归算法
    void AllShow();//都来一遍

    void NLRRecursion(BTreeNode<T>*);//先序递归算法递归部分
    void LNRRecursion(BTreeNode<T>*);//中序递归算法输出递归部分
    void LRNRecursion(BTreeNode<T>*);//后序递归算法递归部分

    void FindAllElder(T);//输出所有长辈，不仅直系

    BTreeNode<T>* find(BTreeNode<T>*,T);//查找

    bool empty();

    int deep(BTreeNode<char>*,BTreeNode<char>*);//树高

    void DestroyCTree(BTreeNode<T>*);//递归销毁

    friend class FamilyTreeSystem;
private:
    BTreeNode<T>* root;//根节点
};

//树字符串检测
template<class T>
void BTree<T>::checkBTreeString(string testString) {
    int num[26] = {0};
    //字符检测,且大写字母不可重复
    for(char c: testString){
        if (isLargeChar(c)){
            if (++num[c-'A']>1){
                throw inputException("家谱中不能出现多次相同的人物，输入失败。");
            }
        }else if (!(isTreeOP(c))){
            throw inputException("输入的括号表达式含有非法字符，输入失败。");
        }
    }

    //首字母检测
    if (!(isLargeChar(testString[0]))){
        throw inputException("第一个字符必须是人物字符，输入失败。");
    }

    //2和末尾字母检测
    if(testString.length()>1 && (testString[1] != '(' || testString[testString.length()-1] != ')')){
        throw inputException("表达式括号错误，输入失败。");
    }

    //单卷册
    for (int i = 1; i < testString.length()-1; ++i) {
        if (isLargeChar(testString[i])){
            if (testString[i-1] == ')' || isLargeChar(testString[i-1]) || isLargeChar(testString[i+1])){
                throw inputException("表达式人物字符左右格式错误，输入失败。");
            }
        } else if (testString[i]=='('){
            if ((!isLargeChar(testString[i-1])) || (testString[i+1] == ')')){
                throw inputException("表达式左括号格式错误，输入失败。");
            }
        } else if (testString[i]==')'){
            if (testString[i-1]=='(' || testString[i+1] == '(' || isLargeChar(testString[i+1])){
                throw inputException("表达式右括号格式错误，输入失败。");
            }
        } else if (testString[i] == ','){
            if (testString[i-1] == ',' || testString[i+1] == ',' || testString[i+1] == '('){
                throw inputException("表达式逗号格式错误，输入失败。");
            }
        }
    }

    //括号栈检测
    LinkStack<char> bracketStack;
    int rootOne = 0;
    for(char c: testString){
        if (c == '(') {
            if (bracketStack.empty()){
                rootOne ++;
                if (rootOne > 1){
                    throw RootException("家谱不能有多个根源，输入失败。");
                }
            }
            bracketStack.push(c);
        } else if (c == ')'){
            if (bracketStack.empty()){
                throw StackEmptyException("表达式左括号不匹配，输入失败。");
            }
            bracketStack.pop();
        }
    }

    if (!bracketStack.empty()){
        throw StackEmptyException("表达式右括号不匹配，输入失败。");
    }

    //逗号检测
    LinkStack<char> commaStack;
    for(char c: testString){
        if (c == '(' || c == ',') {
            commaStack.push(c);
        } else if (c == ')'){
            commaStack.pop();
            if (commaStack.getTop() == ','){
                throw StackEmptyException("表达式逗号不匹配，输入失败。");
            } else if (commaStack.getTop() == '('){
                commaStack.pop();
            } else{
                throw StackEmptyException("未知错误，输入失败。");
            }
        }
    }
}

//空构造函数
template<class T>
BTree<T>::BTree() {
    root = nullptr;
}

//表达式构造构造函数
template<class T>
BTree<T>::BTree(string treeString) {
    root = nullptr;
    buildTree(treeString);
}

//表达式构造
template<class T>
void BTree<T>::buildTree(string treeString){
    checkBTreeString(treeString);
    DestroyCTree(root);//重新构造家谱需要删除原有家谱
    root = nullptr;
    LinkStack<BTreeNode<T>*> elemStack;
    BTreeNode<char>* p;
    bool isLeft = false;
    for(char c: treeString){
        switch (c) {
            case '(':
                elemStack.push(p);
                isLeft = true;
                break;
            case ')':
                elemStack.pop();
                break;
            case ',':
                isLeft = false;
                break;
            default:
                p = new BTreeNode<char>(c);
                if (empty()){
                    root = p;
                } else{
                    if (isLeft && !elemStack.empty()){
                        elemStack.getTop()->lTree = p;
                    } else if (!elemStack.empty()){
                        elemStack.getTop()->rTree = p;
                    } else{
                        throw inputException("未知错误，转换失败。");//真给检测出未知错误了，忘记删除原有数据了
                    }
                }
                break;
        }
    }
}

//析构函数
template<class T>
BTree<T>::~BTree() {
    DestroyCTree(root);
}

//先序递归算法输出
template<class T>
void BTree<T>::NLRRecursionShow(){
    if (empty()){
        throw TreeEmptyException("家谱没有初始化，无法输出。");
    }
    cout<<"先序递归法输出:";
    NLRRecursion(root);
    cout<<endl;
}
template<class T>
void BTree<T>::NLRRecursion(BTreeNode<T>* r) {
    if (r == nullptr){
        return;
    } else{
        cout<<r->data;
        NLRRecursion(r->lTree);
        NLRRecursion(r->rTree);
    }
}

//先序非递归算法输出
template<class T>
void BTree<T>::NLRNoneRecursionShow(){
    if (empty()){
        throw TreeEmptyException("家谱没有初始化，无法输出。");
    }
    cout<<"先序非递归法输出:";
    LinkStack<BTreeNode<char>*> charStack;
    BTreeNode<char>* p = root;
    while (p!= nullptr || !charStack.empty()){
        if (p != nullptr){
            cout<<p->data;
            charStack.push(p);
            p=p->lTree;
        } else {
            p = charStack.pop();
            p=p->rTree;
        }
    }
    cout<<endl;
}

//中序递归算法输出
template<class T>
void BTree<T>::LNRRecursionShow(){
    if (empty()){
        throw TreeEmptyException("家谱没有初始化，无法输出。");
    }
    cout<<"中序递归法输出:";
    LNRRecursion(root);
    cout<<endl;
}
template<class T>
void BTree<T>::LNRRecursion(BTreeNode<T>* r) {
    if (r == nullptr){
        return;
    } else{
        LNRRecursion(r->lTree);
        cout<<r->data;
        LNRRecursion(r->rTree);
    }
}

//中序非递归算法输出
template<class T>
void BTree<T>::LNRNoneRecursionShow(){
    if (empty()){
        throw TreeEmptyException("家谱没有初始化，无法输出。");
    }
    cout<<"中序非递归法输出:";
    LinkStack<BTreeNode<char>*> charStack;
    BTreeNode<char>* p = root;
    while (p!= nullptr || !charStack.empty()){
        if (p != nullptr){
            charStack.push(p);
            p=p->lTree;
        } else {
            p = charStack.pop();
            cout<<p->data;
            p=p->rTree;
        }
    }
    cout<<endl;
}

//后序递归算法
template<class T>
void BTree<T>::LRNRecursionShow(){
    if (empty()){
        throw TreeEmptyException("家谱没有初始化，无法输出。");
    }
    cout<<"后序递归法输出:";
    LRNRecursion(root);
    cout<<endl;
}
template<class T>
void BTree<T>::LRNRecursion(BTreeNode<T>* r) {
    if (r == nullptr){
        return;
    } else{
        LRNRecursion(r->lTree);
        LRNRecursion(r->rTree);
        cout<<r->data;
    }
}

//后序非递归算法
template<class T>
void BTree<T>::LRNNoneRecursionShow(){
    if (empty()){
        throw TreeEmptyException("家谱没有初始化，无法输出。");
    }
    cout<<"后序非递归法输出:";
    LinkStack<BTreeNode<char>*> charStack;
    BTreeNode<char>* p = root;
    BTreeNode<char>* pre = nullptr;
    while (p!= nullptr || !charStack.empty()){
        if (p != nullptr){
            charStack.push(p);
            pre = p;
            p=p->lTree;
        } else {
            p = charStack.getTop();
            if (p->rTree == nullptr || p->rTree == pre){
                cout<<charStack.pop()->data;
                pre = p;
                p = nullptr;
            } else{
                pre = p;
                p = p->rTree;
            }
        }
    }
    cout<<endl;
}

//都来一遍
template<class T>
void BTree<T>::AllShow(){
    NLRRecursionShow();
    NLRNoneRecursionShow();
    LNRRecursionShow();
    LNRNoneRecursionShow();
    LRNRecursionShow();
    LRNNoneRecursionShow();
}

//输出所有长辈，不仅直系
template<class T>
void BTree<T>::FindAllElder(T c){
    if (empty()){
        throw TreeEmptyException("家谱没有初始化，无法输出。");
    }
    cout<<"长辈有:";
    //方法一：利用层次和层次输出
    LinkDoubleEndQueue<BTreeNode<char>*> gradationQueue;//双端队列
    BTreeNode<char>* young = find(root,c);//是否存在
    BTreeNode<char>* p;
    if (young == nullptr){
        throw TreeEmptyException("没有找到该成员，查找失败。");
    }
    int deepYoung = deep(root,young);//目标的深度
    if (c == root->data){
        cout<<"他最大，该家谱中没有其长辈。"<<endl;
        return;
    } else{
        gradationQueue.push(root);
        do {
            p = gradationQueue.pop();
            cout<<p->data;
            if (p->lTree!= nullptr && deep(root,p->lTree) < deepYoung){
                gradationQueue.push(p->lTree);
            }
            if (p->rTree != nullptr && deep(root,p->rTree) < deepYoung){
                gradationQueue.pushFromOtherSide(p->rTree);//优先入双端队列队首
            }
        } while (!gradationQueue.empty());
    }
    cout<<endl;
}

//空
template<class T>
bool BTree<T>::empty() {
    return root == nullptr;
}

//递归销毁
template<class T>
void BTree<T>::DestroyCTree(BTreeNode<T>* b){
    if (b == nullptr){
        return;
    }
    DestroyCTree(b->lTree);
    DestroyCTree(b->rTree);
    delete b;
}

//树深（从上而下）
template<class T>
int BTree<T>::deep(BTreeNode<char> * now,BTreeNode<char>* toFind) {
    if (now == nullptr){
        return -1;
    }
    if (now == toFind){
        return 0;
    }
    int d1 = deep(now->lTree,toFind);
    if (d1 >= 0){
        return d1 + 1;
    }
    d1 = deep(now->rTree,toFind);
    if (d1 >= 0){
        return d1;
    }
    return -1;
}

//查找
template<class T>
BTreeNode<T>* BTree<T>::find(BTreeNode<T>* r,T c){
    if (r == nullptr){
        return nullptr;
    }
    if (r->data == c){
        return r;
    }
    BTreeNode<T>* r2 = find(r->lTree,c);
    if (r2 != nullptr){
        return r2;
    }
    r2 = find(r->rTree,c);
    if (r2 != nullptr){
        return r2;
    }
    return nullptr;
}
#endif //FAMILY_TREE_BTREE_H
