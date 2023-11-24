#include"TreeNode.h"
#include<queue>

using namespace std;

void generate(TreeNode* root, string code, unordered_map<char, string>& map){
    if (root==nullptr){
        return;
    }
    //set the alphabet letter to its code 
    if(root->val != '\0'){
        map[root->val]= code;
    }
    //recursively traverse the tree to generate the huffman code for each node
    generate(root->_left, code + "0", map);
    generate(root->_right, code + "1", map);
}

/*TreeNode* buildTree(const unordered_map<char, float>& freqmap) {
    priority_queue<TreeNode, vector<TreeNode>, greater<TreeNode>> minHeap;

    for (const auto& entry : freqmap) {
        minHeap.push(TreeNode(entry.first, entry.second));
    }

    while (minHeap.size() > 1) {
        TreeNode* left = new TreeNode(minHeap.top().val,minHeap.top().freq);
        minHeap.pop();

        TreeNode* right = new TreeNode(minHeap.top().val,minHeap.top().freq);
        minHeap.pop();

        TreeNode* node = new TreeNode('\0', left->freq + right->freq);
        node->_left = left;
        node->_right = right;

        minHeap.push(*node);
    }
    TreeNode* root = new TreeNode(minHeap.top());
    return root;
}*/
TreeNode* buildTree(const std::unordered_map<char, float>& freqmap) {
    std::priority_queue<TreeNode*, std::vector<TreeNode*>, TreeNode> minHeap;

    for (const auto& entry : freqmap) {
        minHeap.push(new TreeNode(entry.first, entry.second));
    }

    while (minHeap.size() > 1) {
        TreeNode* left = minHeap.top();
        minHeap.pop();

        TreeNode* right = minHeap.top();
        minHeap.pop();

        TreeNode* node = new TreeNode('\0', left->freq + right->freq);
        node->_left = left;
        node->_right = right;

        minHeap.push(node);
    }

    TreeNode* root = minHeap.top();
    return root;
}
