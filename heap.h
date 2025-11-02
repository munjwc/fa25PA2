#ifndef HEAP_H
#define HEAP_H
#include <iostream>
using namespace std;

/*
  Array-based Min-Heap.
  We store node indices, not weights.
  Compare using weightArr[].
*/
const int MAX_NODES = 64;

struct MinHeap {
    int data[MAX_NODES];
    int size;

    MinHeap(){size=0;}

    void push(int idx,int weightArr[]){
        data[size]=idx;
        upheap(size,weightArr);
        size++;
    }

    int pop(int weightArr[]){
        if(size==0) return -1;
        int ret=data[0];
        size--;
        if(size>0){
            data[0]=data[size];
            downheap(0,weightArr);
        }
        return ret;
    }

    void upheap(int pos,int weightArr[]){
        while(pos>0){
            int parent=(pos-1)/2;
            if(weightArr[data[pos]]<weightArr[data[parent]]){
                int t=data[pos];data[pos]=data[parent];data[parent]=t;
                pos=parent;
            }else break;
        }
    }

    void downheap(int pos,int weightArr[]){
        while(true){
            int l=2*pos+1,r=2*pos+2,s=pos;
            if(l<size && weightArr[data[l]]<weightArr[data[s]]) s=l;
            if(r<size && weightArr[data[r]]<weightArr[data[s]]) s=r;
            if(s!=pos){
                int t=data[pos];data[pos]=data[s];data[s]=t;
                pos=s;
            }else break;
        }
    }
};

#endif
