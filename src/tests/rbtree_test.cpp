//
// Created by Rahim Ahmedov on 17.03.23.
//

#include "rbtree_test.h"
#include <random>
#include <ctime>

void RBTreeIntString::print(int uptoLevel) {
    print(getRoot(), 0, 'r', uptoLevel);
}


void RBTreeIntString::print(Node<int, std::string> *node, int lvl, char ind, int uptoLevel ) {
    if (node == nullptr) return;
    if (lvl < uptoLevel || uptoLevel == -1) {
        if (lvl == 0)
            std::cout
                    << node->key << "->" << node->value
                    << "(c:" << (node->color == RED ? "RED" : "BLACK") << ",nc:" << node->nodeCount << ")"
                    << std::endl;
        else {
            int sz = lvl * 3;
            std::string str(sz, ' ');
            str[sz - 3] = '+';
            str[sz - 2] = '-';
            std::cout << str
                      << node->key << "->" << node->value
                      << "(" << ind << ",c:" << (node->color == RED ? "RED" : "BLACK") << ",nc:" << node->nodeCount
                      << ")"
                      << std::endl;
        }
        print(node->right, lvl + 1, 'r', uptoLevel);
        print(node->left, lvl + 1, 'l', uptoLevel);
    }
}

int main() {

    RBTreeIntString rbtree = RBTreeIntString();
    for(int i = 0; i<7; i++)
        rbtree.insert(i, "test");
    rbtree.print();
    std::cout << "-------------------------------------\n";

    rbtree.inOrderAction([&](int k, std::string v, uint64_t nodeCount )->void{
        std::cout << k << "->" << v << ": " << nodeCount << std::endl;
    });

    std::cout << "-------------------------------------\n";

    rbtree = RBTreeIntString();
    for(int i = 0; i<32; i++)
        rbtree.insert(-i, "test");
    rbtree.print();
    std::cout << "-------------------------------------\n";

    rbtree = RBTreeIntString();
    for(int i = 0; i<16; i++) {
        rbtree.insert(-i, "test");
        rbtree.insert(i, "test");
    }
    rbtree.print();


    std::cout << "-------------------------------------\n";

    rbtree = RBTreeIntString();
    std::mt19937 random_gen(static_cast<unsigned int>(std::time(nullptr)));
    std::uniform_int_distribution<int>  distribution(1, 1000);
    for (int i = 0; i < 1000; ++i)
        rbtree.insert(distribution(random_gen), "rand");

    rbtree.print(5);

    std::cout << "-------------------------------------\n";

    std::string val;
    if (rbtree.getValue(666, val))
        std::cout << "contains value 666 " << val << std::endl;
    else
        std::cout << "doesnt contain value 666 \n";
    if (rbtree.getValue(1666, val))
        std::cout << "contains value 1666 " << val << std::endl;
    else
        std::cout << "doesnt contain value 1666 \n";

    return 0;
}

