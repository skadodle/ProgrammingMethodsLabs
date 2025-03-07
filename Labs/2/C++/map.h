#pragma once

#include <iostream>
#include <vector>

using namespace std;

template <typename Key, typename Value>
struct Node {
    pair<Key, Value> data;
    Node* parent;
    Node* leftChild;
    Node* rightChild;

    Node(Key key, Value value) : data(make_pair(key, value)), parent(nullptr), leftChild(nullptr), rightChild(nullptr) {}
    Node() : parent(nullptr), leftChild(nullptr), rightChild(nullptr) {}
};

template <typename Key>
struct Comparator {
    bool operator()(const Key& a, const Key& b) const {
        return a < b;
    }
};

template<typename Key, typename Value, typename Compare = Comparator<Key>>
class Map {
    private:
        Node<Key, Value>* root;
        Compare comp;

        void clearHelper(Node<Key, Value>* node) {
            if (node) {
                clearHelper(node->leftChild);
                clearHelper(node->rightChild);
                delete node;
            }
        }

        Node<Key, Value>* copyTree(Node<Key, Value>* otherRoot, Node<Key, Value>* parent) {
            if (!otherRoot) return nullptr;
            Node<Key, Value>* newNode = new Node<Key, Value>(otherRoot->data.first, otherRoot->data.second);
            newNode->parent = parent;
            newNode->leftChild = copyTree(otherRoot->leftChild, newNode);
            newNode->rightChild = copyTree(otherRoot->rightChild, newNode);
            return newNode;
        }

        void inOrderTraversal(Node<Key, Value>* node, vector<pair<Key, Value>>& nodes) {
            if (!node) return;
            inOrderTraversal(node->leftChild, nodes);
            nodes.push_back(node->data);
            inOrderTraversal(node->rightChild, nodes);
        }
        
        Node<Key, Value>* buildBalancedTree(vector<pair<Key, Value>>& nodes, int start, int end) {
            if (start > end) return nullptr;
            int mid = (start + end) / 2;
            Node<Key, Value>* node = new Node<Key, Value>(nodes[mid].first, nodes[mid].second);
            node->leftChild = buildBalancedTree(nodes, start, mid - 1);
            node->rightChild = buildBalancedTree(nodes, mid + 1, end);
            return node;
        }

    public:
        Map() : root() {}
        ~Map() { clear(); }

        Map(const Map& other) : root() { root = copyTree(other.root, nullptr); }

        Map& operator=(const Map& other) {
            if (this != &other) {
                clear();
                root = copyTree(other.root, nullptr);
            }
            return *this;
        }
        
        bool empty() { return root == nullptr; }
        
        void clear() { clearHelper(root); root = nullptr; }
        
        void insert(const Key& key, const Value& value) {
            Node<Key, Value>* newNode = new Node<Key, Value>(key, value);
            if (!root) {
                root = newNode;
                return;
            }
            auto current = root;
            Node<Key, Value>* parent = nullptr;
            while (current) {
                parent = current;
                if (comp(key, current->data.first))
                    current = current->leftChild;
                else if (comp(current->data.first, key))
                    current = current->rightChild;
                else
                    return;
            }
            newNode->parent = parent;
            if (comp(key, parent->data.first))
                parent->leftChild = newNode;
            else
                parent->rightChild = newNode;
        }
        
        Value& operator[](const Key& key) {
            Value* found = find(key);
            if (found) return *found;
            insert(key, Value());
            return *find(key);
        }
        
        Value* find(const Key& key) {
            auto current = root;
            while (current) {
                if (comp(key, current->data.first))
                    current = current->leftChild;
                else if (comp(current->data.first, key))
                    current = current->rightChild;
                else
                    return &(current->data.second);
            }
            return nullptr;
        }
        
        bool contains(const Key& key) {
            return find(key) != nullptr;
        }
        
        void erase(const Key& key) {
            Node<Key, Value>* current = root;
            Node<Key, Value>* parent = nullptr;
            while (current && current->data.first != key) {
                parent = current;
                if (comp(key, current->data.first))
                    current = current->leftChild;
                else
                    current = current->rightChild;
            }
            if (!current) return;
            
            if (!current->leftChild || !current->rightChild) {
                Node<Key, Value>* child = (current->leftChild) ? current->leftChild : current->rightChild;
                if (!parent)
                    root = child;
                else if (parent->leftChild == current)
                    parent->leftChild = child;
                else
                    parent->rightChild = child;
                delete current;
            }
        }
        
        void printHelper(Node<Key, Value>* node) {
            if (!node) return;
            printHelper(node->leftChild);
            cout << node->data.first << ": " << node->data.second << endl;
            printHelper(node->rightChild);
        }
    
        void print() {
            printHelper(root);
        }
        
        void balance() {
            vector<pair<Key, Value>> nodes;
            inOrderTraversal(root, nodes);
            clear();
            root = buildBalancedTree(nodes, 0, nodes.size() - 1);
        }

        struct Node<Key, Value> node;
};