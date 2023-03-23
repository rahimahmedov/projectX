//
// Created by Rahim Ahmedov on 17.03.23.
//

#ifndef PROJECTX_RBTREE_H
#define PROJECTX_RBTREE_H


#include <cstdint>
#include <functional>

enum COLOR {RED, BLACK};

template <typename K, typename V>
struct Node {
    K key; V value;
    Node *left, *right, *parent;
    uint8_t color ;
    uint64_t nodeCount;
    Node(K k, V v) {
        key = k;
        value = v;
        left = right = parent = nullptr;
        color = RED;
        nodeCount = 1;
    }
};

template <typename K, typename V>
class RBTree {
public:

    RBTree(): root(nullptr) {};

    void insert(K k, V v) {
        Node<K, V> *insertedNode;
        insert(k, v, root, insertedNode);
        fixViolations(insertedNode);
    }

    bool getValue(const K && key,  V &value)  {
        auto node = root;
        if (node->key == key) {
            value = node->value;
            return  true;
        }
        while(node != nullptr && node->key != key ) {
            if (key > node->key)
                node = node->right;
            else
                node = node->left;
            if (node == nullptr)
                return false;
            if (node->key == key) {
                value = node->value;
                return  true;
            }
        }
        return false;
    }

    Node<K,V> * getRoot() {
        return root;
    }

    void inOrderAction(std::function<void(K& key, V& value, uint64_t& nodeCount)> action) {
        if(root != nullptr) {
            inOrderAction(action, root->left);
            action(root->key, root->value, root->nodeCount);
            inOrderAction(action, root->right);
        }
    }

private:

    Node<K,V> *root;

    void insert(K k, V v, Node<K, V>*& node, Node<K, V>*& insertedNode) {
        if (node == nullptr) {
            node = new Node(k, v);
            node->color = BLACK; // root node
            insertedNode = node;
            return;
        }
        if (k > node->key ) {
            if (node->right != nullptr)
                insert(k,v,node->right, insertedNode);
            else {
                node->right = new Node<K,V>(k, v);
                node->right->parent = node;
                insertedNode = node->right;
            }
        }
        else {
            if (node->left != nullptr)
                insert(k, v, node->left, insertedNode);
            else {
                node->left = new Node<K,V>(k, v);
                node->left->parent = node;
                insertedNode = node->left;
            }
        }
        node->nodeCount =
                (node->right == nullptr ? 0 : node->right->nodeCount) +
                (node->left == nullptr ? 0 : node->left->nodeCount) + 1;

    }

    void leftRotate(Node<K, V>* node) {
        Node<K,V>* tmp = node->right;
        node->nodeCount -= tmp->nodeCount;
        node->right = tmp->left;
        node->nodeCount += (tmp->left != nullptr ? tmp->left->nodeCount: 0);
        if (node->right != nullptr)
            node->right->parent = node;
        tmp->parent = node->parent;
        if (node->parent != nullptr) {
            if (tmp->key > node->parent->key)
                tmp->parent->right = tmp;
            else tmp->parent->left = tmp;
        }
        tmp->nodeCount -= (tmp->left != nullptr ? tmp->left->nodeCount: 0);
        tmp->left = node;
        tmp->nodeCount += node->nodeCount;
        node->parent = tmp;
        if (tmp->parent == nullptr)
            root = tmp;
    }

    void rightRotate(Node<K, V>* node){
        Node<K,V>* tmp = node->left;
        node->nodeCount -= tmp->nodeCount;
        node->left = tmp->right;
        node->nodeCount += (tmp->right != nullptr ? tmp->right->nodeCount: 0);
        if (node->left != nullptr)
            node->left->parent = node;
        tmp->parent = node->parent;
        if (node->parent != nullptr) {
            if (tmp->key > node->parent->key)
                tmp->parent->right = tmp;
            else tmp->parent->left = tmp;
        }
        tmp->nodeCount -= (tmp->right != nullptr ? tmp->right->nodeCount: 0);
        tmp->right = node;
        tmp->nodeCount += node->nodeCount;
        node->parent = tmp;
        if (tmp->parent == nullptr)
            root = tmp;
    }

    inline Node<K,V>* getAunt(const Node<K,V>* node) {
        // Im right node
        if (node->parent->right == node) {
            if (node->parent->parent->right == node->parent)
                return  node->parent->parent->left;
            else return node->parent->parent->right;
        }
        // im left node
        if (node->parent->parent->left == node->parent)
            return  node->parent->parent->right;
        else return node->parent->parent->left;
    }

    void fixViolations(Node<K, V>* node) {
        // if root node - fix color if necessary:
        if (node == nullptr) return;
        if (node->parent == nullptr) {
            node->color = BLACK;
            return;
        }
        // 2 consecutive REDs
        if (node->parent->color == RED && node->color == RED) {
            Node<K,V>* aunt = getAunt(node);
            // aunt is RED color flip
            if( aunt != nullptr && aunt->color == RED) {
                //flipColor(node);
                node->parent->parent->color = RED;
                node->parent->color = BLACK;
                aunt->color = BLACK;
                fixViolations(node->parent->parent);
            }
            // aunt is black - rotate
            else {
                // right rotate
                if (node->parent->left == node && node->parent->parent->left == node->parent) {
                    rightRotate(node->parent->parent);
                    node->color = RED;
                    node->parent->color = BLACK;
                    if (node->parent->right != nullptr) node->parent->right->color = RED;
                }
                // left rotate
                else if (node->parent->right == node && node->parent->parent->right == node->parent) {
                    leftRotate(node->parent->parent);
                    node->color = RED;
                    node->parent->color = BLACK;
                    if(node->parent->left != nullptr) node->parent->left ->color = RED;
                }
                // left-right rotate
                else if(node->parent->right == node && node->parent->parent->left == node->parent) {
                    leftRotate(node->parent); // node changed
                    rightRotate(node->parent);
                    node->color = BLACK;
                    node->right->color = RED;
                    node->left->color = RED;
                }
                // right-left rotate
                else if(node->parent->left == node && node->parent->parent->right == node->parent) {
                    rightRotate(node->parent); // node changed
                    leftRotate(node->parent);
                    node->color = BLACK;
                    node->right->color = RED;
                    node->left->color = RED;
                }
                fixViolations(node->parent);
            }
        }
//        fixViolations(node->parent);
    }

    void inOrderAction(std::function<void (K& key,  V& value, uint64_t& nodeCount)> action, Node<K,V>* node) {
        if (node!= nullptr) {
            inOrderAction(action, node->left);
            action(node->key, node->value, node->nodeCount);
            inOrderAction(action, node->right);
        }
    }
};





#endif //PROJECTX_RBTREE_H
