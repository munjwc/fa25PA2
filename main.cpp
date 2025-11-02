#include <iostream>
#include <fstream>
#include <string>
#include "heap.h"
using namespace std;

// global arrays for future steps
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// simple helper functions
static inline bool isUpper(char c){return c>='A'&&c<='Z';}
static inline char toLower(char c){return char(c+('a'-'A'));}
static inline bool isLower(char c){return c>='a'&&c<='z';}

int main(){
    int freq[26]={0};
    ifstream fin("input.txt");
    if(!fin){cerr<<"Error: cannot open input.txt\n";return 1;}
    char ch;
    while(fin.get(ch)){
        if(isUpper(ch)) ch=toLower(ch);
        if(isLower(ch)) freq[ch-'a']++;
    }
    fin.close();
    cout<<"File read complete. Frequencies loaded.\n";
    return 0;
}