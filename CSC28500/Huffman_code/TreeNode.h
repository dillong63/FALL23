#ifndef TREENODE_H
#define TREENODE_H
#include<unordered_map>
#include<string>

class TreeNode{
    public:
        char val;
        float freq;
        TreeNode *_left;
        TreeNode *_right;
        TreeNode() : val(' '), _left(nullptr), _right(nullptr) {}
        TreeNode(char value, float frequ) : val(value), freq(frequ), _left(nullptr), _right(nullptr) {}
        bool operator>(const TreeNode& other) const {
            return freq >other.freq;
        }
 bool operator()(const TreeNode* lhs, const TreeNode* rhs) const {
     return lhs->freq > rhs->freq;
 }


}; 

        TreeNode* buildTree(const std::unordered_map<char , float> & freqmap);
        void generate(TreeNode* root, std::string code, std::unordered_map<char, std::string>& map);
#endif
