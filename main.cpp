#include <iostream>
#include <fstream>
#include <string>
#include "heap.h"
using namespace std;

/*
  Step 3: Build encoding tree (like Huffman Tree)
  - Combine two smallest nodes until one root remains.
*/

const int MAX_NODES=64;
int weightArr[MAX_NODES],leftArr[MAX_NODES],rightArr[MAX_NODES];
char charArr[MAX_NODES];

static inline bool isUpper(char c){return c>='A'&&c<='Z';}
static inline char toLower(char c){return char(c+('a'-'A'));}
static inline bool isLower(char c){return c>='a'&&c<='z';}

void buildFrequencyTable(int freq[],const string& filename){...} // same as before
int createLeafNodes(int freq[]){...} // same as before

int buildEncodingTree(int nextFree){
    if(nextFree==0) return -1;
    if(nextFree==1) return 0;
    MinHeap heap;
    for(int i=0;i<nextFree;i++) heap.push(i,weightArr);
    int current=nextFree;
    while(heap.size>1){
        int a=heap.pop(weightArr);
        int b=heap.pop(weightArr);
        leftArr[current]=a;
        rightArr[current]=b;
        charArr[current]='\0';
        weightArr[current]=weightArr[a]+weightArr[b];
        heap.push(current,weightArr);
        current++;
    }
    return heap.pop(weightArr);
}

int main(){
    int freq[26]={0};
    buildFrequencyTable(freq,"input.txt");
    int nextFree=createLeafNodes(freq);
    int root=buildEncodingTree(nextFree);
    cout<<"Tree built. Root index: "<<root<<"\n";
    return 0;
}
