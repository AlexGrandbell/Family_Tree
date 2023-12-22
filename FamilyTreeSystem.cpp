//
// Created by 沈嘉瑞 on 2023.11.02.
//

#include "FamilyTreeSystem.h"

FamilyTreeSystem::FamilyTreeSystem(){}

FamilyTreeSystem::FamilyTreeSystem(string tmpTree):bTree(tmpTree){}

//显示菜单
void FamilyTreeSystem::FamilyTreeSystem::outPutMenu(){
    cout<<"\n ----------菜单----------"<<endl;
    cout<<" |1.输入家谱            |"<<endl;
    cout<<" |2.输出家谱            |"<<endl;
    cout<<" |3.查看长辈            |"<<endl;
    cout<<" |0.退出程序            |"<<endl;
    cout<<" ------------------------"<<endl;
    //输出提示选择编号
    cout<<"请选择菜单项编号(0-3):";
}

//输入家谱
void FamilyTreeSystem::Input(){
    cout << "----------输入家谱----------" << endl;
    try {
        cout<<"请使用括号表达式法输入家谱树的左孩子右兄弟二叉树(使用不同的大写字母表示一个人):";
        bTree.buildTree(inputString());
        cout<<"家谱创建成功！"<<endl;
    } catch (const exception &e) {
        cerr << e.what() << endl;
    }
    cout << "----------------------------" << endl;
}

//输出家谱
void FamilyTreeSystem::OutPut(){
    cout << "----------输出家谱----------" << endl;
    try {
        cout<<"请选择输出家谱的实现逻辑(1-先序递归,2-先序非递归,3-中序递归,4-中序非递归,5-后序递归,6-后序非递归,7-都来一遍):";
        int choice = inputInt();
        switch (choice) {
            case 1:
                bTree.NLRRecursionShow();
                break;
            case 2:
                bTree.NLRNoneRecursionShow();
                break;
            case 3:
                bTree.LNRRecursionShow();
                break;
            case 4:
                bTree.LNRNoneRecursionShow();
                break;
            case 5:
                bTree.LRNRecursionShow();
                break;
            case 6:
                bTree.LRNNoneRecursionShow();
                break;
            case 7:
                bTree.AllShow();
                break;
            default:
                throw NumberException("无效选择。");
        }
        cout<<"家谱输出完成！"<<endl;
    } catch (const exception &e) {
        cerr << e.what() << endl;
    }
    cout << "----------------------------" << endl;
}

//查看所有长辈
void FamilyTreeSystem::WatchAncestors(){
    cout << "----------查看长辈----------" << endl;
    try {
        cout<<"请输入晚辈的字符:";
        bTree.FindAllElder(inputOneLargeChar());
        cout<<"查找完成"<<endl;
    } catch (const exception &e) {
        cerr << e.what() << endl;
    }
    cout << "----------------------------" << endl;
}

//退出程序
void FamilyTreeSystem::ExitApp(){
    cout<<"\n欢迎再次使用，再见。"<<endl;
}