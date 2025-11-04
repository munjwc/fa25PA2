#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

/*
  Variable-Bit (Frequency-Based) Encoder
  - Build frequency table for a..z (uppercase normalized)
  - Build Huffman-style tree using array-based Min-Heap (node indices only)
  - Generate codes via iterative DFS with std::stack (no recursion)
  - Print code table and encoded message
*/

// With <=26 letters, total nodes <= 51. Use 64 as a safe cap.
const int MAX_NODES = 64;

// Parallel arrays = node storage
int  weightArr[MAX_NODES];  // frequency (weight)
int  leftArr[MAX_NODES];    // left child or -1
int  rightArr[MAX_NODES];   // right child or -1
char charArr[MAX_NODES];    // leaf letter; internal = '\0'

// Tiny helpers (no <cctype>)
static inline bool isUpper(char c){ return c >= 'A' && c <= 'Z'; }
static inline char toLower(char c){ return char(c + ('a' - 'A')); }
static inline bool isLower(char c){ return c >= 'a' && c <= 'z'; }

// Prototypes
void buildFrequencyTable(int freq[], const string& filename);
int  createLeafNodes(int freq[]);
int  buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    const string filename = "input.txt";

    // 1) Frequency analysis
    int freq[26] = {0};
    buildFrequencyTable(freq, filename);

    // 2) Create leaves in global arrays
    int nextFree = createLeafNodes(freq);

    // 3) Build tree with heap (indices only)
    int root = buildEncodingTree(nextFree);

    // 4) Generate codes using iterative DFS (stack)
    string codes[26];
    generateCodes(root, codes);

    // 5) Output code table + encoded message
    encodeMessage(filename, codes);
    return 0;
}

void buildFrequencyTable(int freq[], const string& filename) {
    ifstream fin(filename);
    if (!fin) { cerr << "Cannot open " << filename << "\n"; exit(1); }
    char c;
    while (fin.get(c)) {
        if (isUpper(c)) c = toLower(c);
        if (isLower(c)) freq[c - 'a']++;
    }
    fin.close();
}

int createLeafNodes(int freq[]) {
    for (int i = 0; i < MAX_NODES; i++) {
        charArr[i] = '\0';
        weightArr[i] = 0;
        leftArr[i] = rightArr[i] = -1;
    }
    int nextFree = 0;
    for (int i = 0; i < 26; i++) {
        if (freq[i]) {
            charArr[nextFree]   = char('a' + i);
            weightArr[nextFree] = freq[i];
            nextFree++;
        }
    }
    return nextFree;
}

int buildEncodingTree(int nextFree) {
    if (nextFree == 0) return -1; // nothing to encode
    if (nextFree == 1) return 0;  // single symbol

    MinHeap heap;
    for (int i = 0; i < nextFree; i++) heap.push(i, weightArr);

    int cur = nextFree; // internal node index
    while (heap.size > 1) {
        int a = heap.pop(weightArr);
        int b = heap.pop(weightArr);

        leftArr[cur]  = a;
        rightArr[cur] = b;
        charArr[cur]  = '\0';
        weightArr[cur]= weightArr[a] + weightArr[b];

        heap.push(cur, weightArr);
        cur++;
        if (cur >= MAX_NODES && heap.size > 1) { cerr << "Node capacity exceeded\n"; break; }
    }
    return heap.pop(weightArr); // root index
}

void generateCodes(int root, string codes[]) {
    for (int i = 0; i < 26; i++) codes[i].clear();
    if (root < 0) return;

    stack<pair<int,string>> st;
    st.push({root, ""});

    while (!st.empty()) {
        auto cur = st.top(); st.pop();
        int node = cur.first;
        const string& path = cur.second;

        bool leaf = (leftArr[node] == -1 && rightArr[node] == -1);
        if (leaf) {
            string code = path.empty() ? "0" : path; // single-letter case
            char ch = charArr[node];
            if (ch >= 'a' && ch <= 'z') codes[ch - 'a'] = code;
        } else {
            // Push right first so left is processed first (stack = LIFO)
            if (rightArr[node] != -1) st.push({ rightArr[node], path + '1' });
            if (leftArr[node]  != -1) st.push({ leftArr[node],  path + '0' });
        }
    }
}

void encodeMessage(const string& filename, string codes[]) {
    cout << "Character : Code\n";
    for (int i = 0; i < 26; i++)
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";

    cout << "\nEncoded message:\n";
    ifstream fin(filename);
    if (!fin) { cerr << "Cannot reopen file\n"; return; }
    char c;
    while (fin.get(c)) {
        if (isUpper(c)) c = toLower(c);
        if (isLower(c)) cout << codes[c - 'a'];
    }
    fin.close();
    cout << "\n";
}
