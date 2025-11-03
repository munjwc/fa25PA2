#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

/*
  Step 4: Generate binary codes (no recursion)
  - Left edge adds '0', right edge adds '1'
  - Use stack to simulate DFS traversal
*/

const int MAX_NODES=64;
int weightArr[MAX_NODES],leftArr[MAX_NODES],rightArr[MAX_NODES];
char charArr[MAX_NODES];

static inline bool isUpper(char c){return c>='A'&&c<='Z';}
static inline char toLower(char c){return char(c+('a'-'A'));}
static inline bool isLower(char c){return c>='a'&&c<='z';}

void buildFrequencyTable(int freq[],const string& f){...}
int createLeafNodes(int freq[]){...}
int buildEncodingTree(int nextFree){...}

void generateCodes(int root,string codes[]){
    for(int i=0;i<26;i++) codes[i].clear();
    if(root<0) return;
    stack<pair<int,string>> st;
    st.push({root,""});
    while(!st.empty()){
        auto cur=st.top();st.pop();
        int node=cur.first;
        string path=cur.second;
        bool leaf=(leftArr[node]==-1&&rightArr[node]==-1);
        if(leaf){
            string code=path.empty()?"0":path;
            char ch=charArr[node];
            if(ch>='a'&&ch<='z') codes[ch-'a']=code;
        }else{
            if(rightArr[node]!=-1) st.push({rightArr[node],path+'1'});
            if(leftArr[node]!=-1)  st.push({leftArr[node], path+'0'});
        }
    }
}

int main(){
    int freq[26]={0};
    buildFrequencyTable(freq,"input.txt");
    int nextFree=createLeafNodes(freq);
    int root=buildEncodingTree(nextFree);
    string codes[26];
    generateCodes(root,codes);
    cout<<"Codes generated.\n";
    return 0;
}
