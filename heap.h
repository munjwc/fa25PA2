#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

/*
  Array-based Min-Heap that stores NODE INDICES (not weights).
  - Compare by weightArr[index]; if equal, prefer smaller index (stable).
  - Parent = (i-1)/2, Left = 2*i+1, Right = 2*i+2
*/
const int MAX_NODES = 64;

struct MinHeap {
    int data[MAX_NODES];
    int size;

    MinHeap() : size(0) {}

    // Compare heap slots a,b by (weight, index)
    bool lessByWeightThenIndex(int a, int b, int weightArr[]) {
        int wa = weightArr[data[a]], wb = weightArr[data[b]];
        if (wa != wb) return wa < wb;
        return data[a] < data[b];
    }

    void push(int idx, int weightArr[]) {
        data[size] = idx;
        upheap(size, weightArr);
        size++;
    }

    int pop(int weightArr[]) {
        if (size == 0) return -1;
        int top = data[0];
        size--;
        if (size > 0) {
            data[0] = data[size];
            downheap(0, weightArr);
        }
        return top;
    }

    void upheap(int pos, int weightArr[]) {
        while (pos > 0) {
            int p = (pos - 1) / 2;
            if (lessByWeightThenIndex(pos, p, weightArr)) {
                int t = data[pos]; data[pos] = data[p]; data[p] = t;
                pos = p;
            } else break;
        }
    }

    void downheap(int pos, int weightArr[]) {
        while (true) {
            int l = 2 * pos + 1, r = 2 * pos + 2, s = pos;
            if (l < size && lessByWeightThenIndex(l, s, weightArr)) s = l;
            if (r < size && lessByWeightThenIndex(r, s, weightArr)) s = r;
            if (s != pos) {
                int t = data[pos]; data[pos] = data[s]; data[s] = t;
                pos = s;
            } else break;
        }
    }
};

#endif // HEAP_H
