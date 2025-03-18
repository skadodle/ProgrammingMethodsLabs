#pragma once

#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>

template <typename Key, typename Value, typename Compare = std::less<Key>>
class BTreeMap {
private:
    struct Node {
        bool isLeaf;
        std::vector<std::pair<Key, Value>> keys;
        std::vector<Node*> children;
        
        Node(bool leaf) : isLeaf(leaf) {}
    };

    Node* root;
    int t;
    Compare comp;

    void splitChild(Node* parent, int index);
    void insertNonFull(Node* node, const Key& key, const Value& value);
    bool search(Node* node, const Key& key, Value& value);
    void clear(Node* node);
    Node* copyNode(const Node* node);
    void printNode(Node* node, int level);

public:
    BTreeMap(int degree) : t(degree), root(nullptr) {}
    ~BTreeMap() { clear(); }
    
    BTreeMap(const BTreeMap& other);
    BTreeMap& operator=(const BTreeMap& other);

    bool empty() { return root == nullptr; }
    void insert(const Key& key, const Value& value);
    bool find(const Key& key, Value& value);
    void clear();
    Value& operator[](const Key& key);
    void print();
};

template <typename Key, typename Value, typename Compare>
void BTreeMap<Key, Value, Compare>::clear(Node* node) {
    if (!node) return;
    if (!node->isLeaf) {
        for (auto* child : node->children) {
            clear(child);
        }
    }
    delete node;
}

template <typename Key, typename Value, typename Compare>
void BTreeMap<Key, Value, Compare>::clear() {
    clear(root);
    root = nullptr;
}

template <typename Key, typename Value, typename Compare>
BTreeMap<Key, Value, Compare>::BTreeMap(const BTreeMap& other) : t(other.t), comp(other.comp) {
    root = copyNode(other.root);
}

template <typename Key, typename Value, typename Compare>
BTreeMap<Key, Value, Compare>& BTreeMap<Key, Value, Compare>::operator=(const BTreeMap& other) {
    if (this != &other) {
        clear();
        t = other.t;
        comp = other.comp;
        root = copyNode(other.root);
    }
    return *this;
}

template <typename Key, typename Value, typename Compare>
typename BTreeMap<Key, Value, Compare>::Node* BTreeMap<Key, Value, Compare>::copyNode(const Node* node) {
    if (!node) return nullptr;
    Node* newNode = new Node(node->isLeaf);
    newNode->keys = node->keys;
    for (const auto* child : node->children) {
        newNode->children.push_back(copyNode(child));
    }
    return newNode;
}

template <typename Key, typename Value, typename Compare>
void BTreeMap<Key, Value, Compare>::insert(const Key& key, const Value& value) {
    if (!root) {
        root = new Node(true);
        root->keys.push_back({key, value});
        return;
    }
    if (root->keys.size() == 2 * t - 1) {
        Node* newRoot = new Node(false);
        newRoot->children.push_back(root);
        splitChild(newRoot, 0);
        root = newRoot;
    }
    insertNonFull(root, key, value);
}

template <typename Key, typename Value, typename Compare>
void BTreeMap<Key, Value, Compare>::splitChild(Node* parent, int index) {
    Node* child = parent->children[index];
    Node* newChild = new Node(child->isLeaf);
    
    int mid = t - 1;
    parent->keys.insert(parent->keys.begin() + index, child->keys[mid]);
    parent->children.insert(parent->children.begin() + index + 1, newChild);

    newChild->keys.assign(child->keys.begin() + t, child->keys.end());
    child->keys.resize(mid);

    if (!child->isLeaf) {
        newChild->children.assign(child->children.begin() + t, child->children.end());
        child->children.resize(mid + 1);
    }
}

template <typename Key, typename Value, typename Compare>
void BTreeMap<Key, Value, Compare>::insertNonFull(Node* node, const Key& key, const Value& value) {
    int i = node->keys.size() - 1;
    if (node->isLeaf) {
        node->keys.push_back({key, value});
        std::sort(node->keys.begin(), node->keys.end(), [this](const auto& a, const auto& b) {
            return comp(a.first, b.first);
        });
    } else {
        while (i >= 0 && comp(key, node->keys[i].first)) {
            --i;
        }
        ++i;
        if (node->children[i]->keys.size() == 2 * t - 1) {
            splitChild(node, i);
            if (comp(node->keys[i].first, key)) {
                ++i;
            }
        }
        insertNonFull(node->children[i], key, value);
    }
}

template <typename Key, typename Value, typename Compare>
bool BTreeMap<Key, Value, Compare>::find(const Key& key, Value& value) {
    return search(root, key, value);
}

template <typename Key, typename Value, typename Compare>
bool BTreeMap<Key, Value, Compare>::search(Node* node, const Key& key, Value& value) {
    if (!node) return false;
    int i = 0;
    while (i < node->keys.size() && comp(node->keys[i].first, key)) {
        ++i;
    }
    if (i < node->keys.size() && !comp(key, node->keys[i].first)) {
        value = node->keys[i].second;
        return true;
    }
    return !node->isLeaf && search(node->children[i], key, value);
}

template <typename Key, typename Value, typename Compare>
Value& BTreeMap<Key, Value, Compare>::operator[](const Key& key) {
    Value value;
    if (!find(key, value)) {
        insert(key, Value());
    }
    find(key, value);
    return value;
}

template <typename Key, typename Value, typename Compare>
void BTreeMap<Key, Value, Compare>::print() {
    if (root) {
        printNode(root, 0); // Начинаем с корня на уровне 0
    } else {
        std::cout << "The tree is empty." << std::endl;
    }
}

template <typename Key, typename Value, typename Compare>
void BTreeMap<Key, Value, Compare>::printNode(Node* node, int level) {
    // Выводим отступы для визуализации уровня узла
    std::cout << std::string(level * 2, ' ') << "Node: ";
    
    // Печатаем ключи и значения в текущем узле
    for (const auto& kv : node->keys) {
        std::cout << "[" << kv.first << ": " << kv.second << "] ";
    }
    std::cout << std::endl;
    
    // Если узел не лист, рекурсивно вызываем printNode для каждого дочернего узла
    if (!node->isLeaf) {
        for (auto* child : node->children) {
            printNode(child, level + 1);  // Увеличиваем уровень для дочернего узла
        }
    }
}