#include <iostream>
#include "priority-queue.h"

int main(int argc, char* argv[]) {
    PriorityQueue pq(10);

    for (int i = 0; i < 25; i++)
        pq.push(i);

    pq.print();

    cout << "Top element " << pq.top() << endl;

    cout << "Size: " << pq.getSize() << endl;

    while(!pq.isEmpty()) {
        cout << pq.pop() << " ";
    }
    cout << endl;

    return 0;
}
