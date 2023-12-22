//
// Created by 沈嘉瑞 on 2023.11.02.
//

#ifndef FAMILY_TREE_FAMILYTREESYSTEM_H
#define FAMILY_TREE_FAMILYTREESYSTEM_H
#include "BTree.h"

class FamilyTreeSystem {
private:
    BTree<char> bTree;
public:
    FamilyTreeSystem();
    FamilyTreeSystem(string);

    void outPutMenu();

    void Input();
    void OutPut();
    void WatchAncestors();

    void ExitApp();
};

#endif //FAMILY_TREE_FAMILYTREESYSTEM_H
