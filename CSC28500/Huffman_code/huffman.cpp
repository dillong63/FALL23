#include<iostream>
#include<unordered_map>
#include"TreeNode.h"
#include<string>
#include <iomanip>

using namespace std;

void printTree(TreeNode* root, int level = 0, char branch = '-') {
    if (root != nullptr) {
        printTree(root->_right, level + 1, '/');
        cout << setw(3 * level) << branch << root->val << " (" << root->freq << ")" << endl;
        printTree(root->_left, level + 1, '\\');
    }
}

int main(int argc, char *argv[]){
    //Frequency table below
    unordered_map<char,float> alp={{'A',0.0817},
    {'B',0145},
    {'C',0.0247},
    {'D',0.0431},
    {'E',0.1232},
    {'F',0.0209},
    {'G',0.0182},
    {'H',0.0668},
    {'I',0.0689},
    {'J',0.0010},
    {'k',0.0080},
    {'L',0.0397},
    {'M',0.0277},
    {'N',0.0662},
    {'O',0.0781},
    {'P',0.0156},
    {'Q',0.0009},
    {'R',0.0572},
    {'S',0.0628},
    {'T',0.0905},
    {'U',0.0304},
    {'V',0.0102},
    {'W',0.0264},
    {'X',0.0015},
    {'Y',0.0211},
    {'Z',0.0005}
    };
    //sends the frequency table to my function to build the tree
    TreeNode* htree= buildTree(alp);
    printTree(htree);
    unordered_map<char, string> huffmanCodes;
    generate(htree,"",huffmanCodes);

    cout<<"The codes are: " << endl;
    for(const auto& p: huffmanCodes){
        cout<< p.first << " = " << p.second <<endl;
    }

    return 0;

}