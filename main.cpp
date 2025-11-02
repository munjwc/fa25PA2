#include <iostream>
#include <fstream>
#include <string>
#include "heap.h"
using namespace std;

/*
  Step 2: Create leaf nodes for each letter that appears.
  - Each node has: character, frequency, left=-1, right=-1
*/

const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

static inline bool isUpper(char c){return c>='A'&&c<='Z';}
static inline char toLower(char c){return char(c+('a'-'A'));}
static inline bool isLower(char c){return c>='a'&&c<='z';}

void buildFrequencyTable(int freq[],const string& filename){
    ifstream f(filename);
    if(!f.is_open()){cerr<<"cannot open "<<filename<<"\n";exit(1);}
    char ch;
    while(f.get(ch)){
        if(isUpper(ch)) ch=toLower(ch);
        if(isLower(ch)) freq[ch-'a']++;
    }
    f.close();
    cout<<"Frequency table built.\n";
}

int createLeafNodes(int freq[]){
    for(int i=0;i<MAX_NODES;i++){
        charArr[i]='\0';
        weightArr[i]=0;
        leftArr[i]=rightArr[i]=-1;
    }
    int nextFree=0;
    for(int i=0;i<26;i++){
        if(freq[i]>0){
            charArr[nextFree]=char('a'+i);
            weightArr[nextFree]=freq[i];
            nextFree++;
        }
    }
    cout<<"Created "<<nextFree<<" leaf nodes.\n";
    return nextFree;
}

int main(){
    int freq[26]={0};
    buildFrequencyTable(freq,"input.txt");
    int nextFree=createLeafNodes(freq);
    return 0;
}
