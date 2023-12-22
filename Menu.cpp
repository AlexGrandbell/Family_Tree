//
// Created by 沈嘉瑞 on 2023.11.02.
//

#include "Menu.h"

void Menu::Welcome() {
    try {
        cout << "\n欢迎进入家谱系统" << endl;
        cout << "你可以随时输入'q'来退出当前操作。" << endl;
        cout << "----------任意输入以开始----------" << endl;
        string tmp = inputString();
        cout << endl;
    }catch (const exception &e) {
        cerr << e.what() << endl;
    }
}

void Menu::DoMenu() {
    FamilyTreeSystem familyTreeSystem;
    int nSelection = -1;//判断用户输入的数字选择对应的菜单
    //不断循环，执行操作
    do {
        //界面与输入
        familyTreeSystem.outPutMenu();//界面
        fflush(stdin);//清除输入流缓存
        nSelection = -1;
        try {
            nSelection = inputInt();

            //根据输入选择行为
            switch (nSelection) {
                case 0: {
                    familyTreeSystem.ExitApp();
                    return;
                }//再见
                case 1: {
                    familyTreeSystem.Input();
                    break;
                }//输入
                case 2: {
                    familyTreeSystem.OutPut();
                    break;
                }//输出
                case 3: {
                    familyTreeSystem.WatchAncestors();
                    break;
                }//查看
                default: {
                    printf("您输入的菜单序号错误,");
                    break;
                }//错误
            }//完成
        } catch (const exception &e) {
            cerr << e.what() << endl;
        }
        if (nSelection != 0) {
            printf("继续操作请按1，关闭程序请按0:");
            fflush(stdin);//清除输入流缓存
            nSelection = -1;
            try {
                nSelection = inputInt();
                if (nSelection == 0) {
                    familyTreeSystem.ExitApp();
                }
            }catch  (const exception& e){
                cerr<<e.what()<<endl;
            }
        }
    } while (nSelection != 0);
}