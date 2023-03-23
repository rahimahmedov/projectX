//
// Created by Rahim Ahmedov on 17.03.23.
//

#ifndef PROJECTX_RBTREE_TEST_H
#define PROJECTX_RBTREE_TEST_H

#include <iostream>
#include "../lsmtree/rbtree.h"

class RBTreeIntString: public RBTree<int, std::string> {
public:
    void print(int uptoLevel=-1);
private:
    void print(Node<int, std::string> * node, int lvl, char ind, int uptoLevel = -1);
};



#endif //PROJECTX_RBTREE_TEST_H
