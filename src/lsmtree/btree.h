//
// Created by Rahim Ahmedov on 08.09.23.
//

#ifndef PROJECTX_BTREE_H
#define PROJECTX_BTREE_H

#include <cstdint>

template <typename K, typename V>
struct Data {
    K key;
    V value;
    friend bool operator > (const Data& d1, const Data& d2);
};

template <typename K, typename V>
bool operator > (const Data<K,V>& d1, const Data<K,V>& d2) {
    return d1.key > d2.key;
};

template <typename K, typename V, uint32_t KEY_DEGREE>
struct BTreeNode {
    Data<K,V> data[KEY_DEGREE + 1];
    BTreeNode<K,V,KEY_DEGREE>* childNodes[KEY_DEGREE + 2];
    BTreeNode<K,V,KEY_DEGREE> *parentNode;
    bool isLeaf;
    uint32_t keyCount; // number of keys, maximum number to hold

    // -- constructor/destructor --
    explicit BTreeNode() :
            parentNode(nullptr),
            isLeaf(true),
            keyCount(0) {}

    ~BTreeNode() {
        parentNode = nullptr;
        for(int i=0; i<=this->keyCount; i++)
            delete childNodes[i];
    }
};

template<typename K, typename V, uint32_t KEY_DEGREE>
class BTree {
public:

    // constructor/destructor
    BTree(): rootNode(new BTreeNode<K,V,KEY_DEGREE>()) {}
    ~BTree() {
        delete rootNode;
    }

    // -- common methods:
    bool search(K& key, V*& resultValue) {
        return search(key, resultValue, rootNode);
    }

    void insert( K& key, V& value) {
        /*
         * Algorithm:
         *  1. get leaf node for insert - getLeafNode()
         *  2. insert into leaf node - insertIntoNode()
         *  3. if element key count in  node >= keyDegree:
         *      3.1 split node in from middle element - splitNode()
         *      3.2 insert middle node to parent node - insertIntoNode()
         *      3.3 go to step 3
         */
        auto insertLeafNode = getLeafNode(key, rootNode);
        insertIntoNode(key, value, insertLeafNode);

    }

    BTreeNode<K,V,KEY_DEGREE>* getRoot() const {
        return rootNode;
    }


private:

    BTreeNode<K,V,KEY_DEGREE>* rootNode;

    uint32_t getKeyPosition(K& key, BTreeNode<K,V,KEY_DEGREE>* node) {
        uint32_t i =0;
        while (i < node->keyCount && (node->data[i]).key < key)
            i++;
        return i;
    }

    bool search(K& key, V*& resultValue, BTreeNode<K,V,KEY_DEGREE>* startNode ) {
        if (startNode == nullptr) return false;
        auto i = getKeyPosition(key, startNode);
        if( (startNode->data[i]).key == key) {
            *resultValue = (startNode->data[i]).value;
            return true;
        }
        if(! startNode->isLeaf) {
            if ((startNode->data[i]).key < key)
                return search(key, resultValue, startNode->childNodes[i]);
            if ((startNode->data[i]).key > key )
                return search(key, resultValue, startNode->childNodes[i+1]);
        }
        return false;
    }

    BTreeNode<K,V,KEY_DEGREE>* getLeafNode(K& key, BTreeNode<K,V,KEY_DEGREE>* startNode) {
        if (startNode->isLeaf) return startNode;
        auto i = getKeyPosition(key, startNode);
        if (i == startNode->keyCount) i--;
        if (startNode->data[i].key >= key)
            return getLeafNode(key,  startNode->childNodes[i]);
        return getLeafNode(key,  startNode->childNodes[i+1]);
    }

    void insertIntoNode(K& key, V& value, BTreeNode<K,V,KEY_DEGREE>* insertNode) {
        auto i = getKeyPosition(key, insertNode);
        insertNode->keyCount++;
        for(uint32_t idx = insertNode->keyCount-1; idx > i; idx--)
            insertNode->data[idx] = insertNode->data[idx-1];
        insertNode->data[i] =  Data<K,V>{key, value};
        if (insertNode->keyCount > KEY_DEGREE) {
            auto insParent =insertNode->parentNode;
            auto newNode = splitNode(insertNode);
            mergeNodes(newNode, insParent);
        }
    }

    BTreeNode<K,V,KEY_DEGREE>* splitNode(BTreeNode<K,V,KEY_DEGREE>* node) {

        auto resNode    = new BTreeNode<K,V,KEY_DEGREE>();
        auto leftChild  = new BTreeNode<K,V,KEY_DEGREE>();
        auto rightChild = new BTreeNode<K,V,KEY_DEGREE>();

        uint32_t splitPos = (node->keyCount -1) / 2 ;
        resNode->keyCount = 1;
        resNode->data[0] = node->data[splitPos]; // same as &(node->data[splitPos])

        for (uint32_t i = 0; i < splitPos; i++) {
            leftChild->data[i] = node->data[i];
            leftChild->keyCount++;
        }
        leftChild->parentNode = resNode;

        for (uint32_t i = splitPos+1, k=0; i < node->keyCount; i++, k++) {
            rightChild->data[k] = node->data[i];
            rightChild->keyCount++;
        }
        rightChild->parentNode = resNode;

        resNode->childNodes[0] = leftChild;
        resNode->childNodes[1] = rightChild;
        resNode->isLeaf = false;

        if (!node->isLeaf) {
            leftChild->isLeaf = false;
            for(uint32_t i = 0; i <= splitPos; i++) {
                leftChild->childNodes[i] = node->childNodes[i];
                leftChild->childNodes[i]->parentNode = leftChild;
            }
            rightChild->isLeaf = false;
            for(uint32_t i = splitPos+1, k=0; i <=node->keyCount; i++, k++) {
                rightChild->childNodes[k] = node->childNodes[i];
                rightChild->childNodes[k]->parentNode = rightChild;
            }
        }

        return  resNode;

    }

    void mergeNodes(BTreeNode<K,V,KEY_DEGREE>* srcNode, BTreeNode<K,V,KEY_DEGREE>* dstNode) {
        if (dstNode == nullptr) rootNode = srcNode;
        else {
            auto key = srcNode->data[0].key;
            auto value = srcNode->data[0].value;
            auto i = getKeyPosition(key, dstNode);
            dstNode->keyCount++;
            for(uint32_t idx = dstNode->keyCount-1; idx > i; idx--)
                dstNode->data[idx] = dstNode->data[idx-1];
            dstNode->data[i] = Data<K,V>{key, value};
            for(uint32_t idx = dstNode->keyCount; idx > i; idx--)
                dstNode->childNodes[idx] = dstNode->childNodes[idx - 1];
            dstNode->childNodes[i] = srcNode->childNodes[0];
            dstNode->childNodes[i+1] = srcNode->childNodes[1];
            dstNode->childNodes[i]->parentNode = dstNode;
            dstNode->childNodes[i+1]->parentNode = dstNode;

            if (dstNode->keyCount > KEY_DEGREE) {
                auto dstParent = dstNode->parentNode;
                auto newNode = splitNode(dstNode);
                mergeNodes(newNode, dstParent);
            }
        }
    };

};

#endif //PROJECTX_BTREE_H
