#ifndef codetree_h
#define codetree_h
#include <vector>
#include <array>
using namespace std;

void printChar(int ch) {
    if( ch < 16 ) {
        std::cout << "x0" << hex << ch;
    } else if( ch < 32 || ch > 126 ) {
        std::cout << "x" << std::hex << ch;
    } else {
        std::cout << "\"" << (char)ch << "\"";
    }
}


struct TreeNode {
    TreeNode *right, *left;
    char ch;
    int freq;
    
    TreeNode(char data, int f){
        left = nullptr;
        right = nullptr;
        ch = data;
        freq = f;
    }
    
    TreeNode(char data, int f, TreeNode * l, TreeNode * r){
        left = l;
        right = r;
        ch = data;
        freq = f;
    }
};

void printCodeHelper( TreeNode * r, string path = ""){
    if (r == NULL) return;
    if (r->right == NULL){
        printChar(r->ch);
        cout << ":" << path << endl;
    }
    else {
        string path2 = path;
        printCodeHelper(r->left, path.append("0"));
        printCodeHelper(r->right, path2.append("1"));
    }
    
}

void printTreeHelper( TreeNode * r, string pre ) {
    if( r == NULL ) return;
    if( r->right == NULL ) { // implies r->left == NULL
        printChar(r->ch);
        std::cout << std::endl;
    } else {
        std::cout << "." << std::endl;
        std::cout << pre << "|`1-";
        printTreeHelper(r->right, pre + "|   ");
        std::cout << pre + "|   " << std::endl;
        std::cout << pre << "`-0-";
        printTreeHelper(r->left, pre + "    ");
    }
}

TreeNode* smallest(vector<TreeNode*> &list){
    int x = 0;
    TreeNode * result = list[x];
    for (int n = 0; n < list.size(); n++){
        if (list[n]->freq <= result->freq){
            result = list[n];
            x = n;
        }
    }
    list.erase(list.begin() + x);
    return result;
}

//Priority Queue as a heap:
struct CodeTree {
    vector<TreeNode *> ct;
    CodeTree(int* freq){
        for (int i = 0; i < 256; i++){
            if (freq[i] != 0){
                TreeNode * temp = new TreeNode((char)i, freq[i]);
                ct.push_back(temp);
            }
        }
        while (ct.size() > 1){
            TreeNode * a = smallest(ct);
            TreeNode * b = smallest(ct);
            TreeNode * sum = new TreeNode(NULL, a->freq + b->freq, a, b);
            ct.push_back(sum);
        }
    
    }
    
    TreeNode * pop(){
        return ct[0];
    }
    
    void printTree(){
        printTreeHelper(pop(), " ");
    }
    
    void printCode(){
        printCodeHelper(pop());
    }
};

 
#endif /* codetree_h */
