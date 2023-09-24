//
// Created by Rahim Ahmedov on 17.09.23.
//

#include <iostream>
#include "../lsmtree/btree.h"


#ifndef PROJECTX_BTREE_TEST_H
#define PROJECTX_BTREE_TEST_H

template <uint32_t KEY_DEGREE>
class BTreeString: public BTree<int,std::string,KEY_DEGREE> {
public:
    explicit BTreeString() : BTree<int,std::string,KEY_DEGREE>() {};
    void print() {
        auto rootNode = this->getRoot();
        print(rootNode, 0);
    };
private:
    void print(BTreeNode<int,std::string,KEY_DEGREE>* node, int lvl){
        if (node == nullptr) return;
        int sz = lvl * 3;
        std::string str(sz, ' ');
        std::cout << str << "(" << node->keyCount << ") ";
        if (node->isLeaf) std::cout << "leaf " ;
        else std::cout << "non-leaf ";
        for(uint32_t i = 0; i < node->keyCount; i++)
            std::cout << node->data[i].key << ":" << node->data[i].value << ",";
        std::cout << std::endl;
        if (node->isLeaf) return;
        for (uint32_t i = 0; i <= node->keyCount; i++)
            print(node->childNodes[i], lvl+1);
    };
};

#endif //PROJECTX_BTREE_TEST_H
