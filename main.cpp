#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

/*
  Step 5: Print the results
  - Print code table (letter → code)
  - Then print encoded message bits
*/

const int MAX_NODES=64;
int weightArr[MAX_NODES],leftArr[MAX_NODES],rightArr[MAX_NODES];
char charArr[MAX_NODES];

static inline bool isUpper(char c){return c>='A'&&c<='Z';}
static inline char toLower(char c){return char(c+('a'-'A'));}
static inline bool isLower(char c){return c>='a'&&c<='z';}

void buildFrequencyTable(int freq[],const string& filename){...}
int createLeafNodes(int freq[]){...}
int buildEncodingTree(int nextFree){...}
void generateCodes(int root,string codes[]){...}

void encodeMessage(const string& filename,string codes[]){
    cout<<"\nCharacter : Code\n";
    for(int i=0;i<26;i++)
        if(!codes[i].empty())
            cout<<char('a'+i)<<" : "<<codes[i]<<"\n";
    cout<<"\nEncoded message:\n";
    ifstream f(filename);
    if(!f.is_open()){cerr<<"cannot reopen\n";return;}
    char ch;
    while(f.get(ch)){
        if(isUpper(ch)) ch=toLower(ch);
        if(isLower(ch)) cout<<codes[ch-'a'];
    }
    cout<<"\n";
    f.close();
}

int main(){
    int freq[26]={0};
    buildFrequencyTable(freq,"input.txt");
    int nextFree=createLeafNodes(freq);
    int root=buildEncodingTree(nextFree);
    string codes[26];
    generateCodes(root,codes);
    encodeMessage("input.txt",codes);
    return 0;
}
