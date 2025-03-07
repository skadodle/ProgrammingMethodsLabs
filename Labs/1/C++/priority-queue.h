#pragma once

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

template <typename T = int, typename K = vector<int>>
class PriorityQueue {
    private:
        class BinaryHeap {
            private:
                K heapArray;

                ssize_t leftChild(size_t index) {
                    if (index * 2 + 1 >= size())
                        return -1;
                    return index * 2 + 1;
                }
                ssize_t rightChild(size_t index) {
                    if (index * 2 + 2 >= size())
                        return -1;
                    return index * 2 + 2;
                }
                ssize_t parent(size_t index) {
                    if (index == 0)
                        return -1;
                    return floor((index - 1) / 2);
                }

                void swap(size_t i, size_t j) {
                    T temp = heapArray[i];
                    heapArray[i] = heapArray[j];
                    heapArray[j] = temp;
                }

            public:
                BinaryHeap(size_t size) {
                    heapArray.reserve(size);
                }
                ~BinaryHeap() { }

                size_t size() { return heapArray.size(); }
                ssize_t curPos() { return heapArray.size() - 1; }

                void push(T el) {
                    heapArray.push_back(el);
                    ssize_t pos = curPos();
                    ssize_t par = parent(pos);
                    while (par != -1 && heapArray[par] < heapArray[pos]) {
                        swap(par, pos);
                        pos = par;
                        par = parent(pos);
                    } 
                }

                T pop() {
                    if (size() == 0)
                        throw "Empty array!";
                    
                    T el = heapArray[0];

                    heapArray[0] = heapArray[size() - 1];
                    heapArray.pop_back();

                    ssize_t pos = 0;
                    ssize_t lChild = leftChild(pos);
                    ssize_t rChild = rightChild(pos);

                    while ((lChild != -1 && heapArray[pos] < heapArray[lChild]) || (rChild != -1 && heapArray[pos] < heapArray[rChild])) {
                        if (heapArray[rChild] < heapArray[lChild]) {
                            swap(pos, lChild);
                            pos = lChild;
                        }
                        else {
                            swap(pos, rChild);
                            pos = rChild;
                        }
                        lChild = leftChild(pos);
                        rChild = rightChild(pos);
                    }

                    return el;
                }

                T peek() {
                    if (size() == 0) 
                        throw "Empry array!";
                    return heapArray[0];
                }

                void print() {
                    for (auto el : heapArray)
                        cout << el << " ";
                    cout << endl;
                }
        };

        BinaryHeap heap;
    
    public:
        PriorityQueue(size_t size) : heap(size) { }
        ~PriorityQueue() { }

        size_t getSize() { return heap.size(); }
        bool isEmpty() { return getSize() == 0; }
        void push(T el) { heap.push(el); }
        T pop() { return heap.pop(); }
        T top() { return heap.peek(); }

        void print() { heap.print(); }
};