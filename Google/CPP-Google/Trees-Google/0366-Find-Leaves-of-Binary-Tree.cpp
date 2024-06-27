/////////////////////////////////////////////////////////////////////////////////////////////////////
//                             0366. Find Leaves of Binary Tree  
//
//
//  Given the root of a binary tree, collect a tree's nodes as if you were doing this:
// 
//              - Collect all the leaf nodes.
//              - Remove all the leaf nodes.
//              - Repeat until the tree is empty.
// 
// Example 1
// Input: root = [1,2,3,4,5]
// Output: [[4,5,3],[2],[1]]
// Explanation:
// [[3,5,4],[2],[1]] and [[3,4,5],[2],[1]] 
// are also considered correct answers since per each level it does not matter the order on which elements are returned.
// 
// Example 2:
// 
// Input: root = [1] Output: [[1]]
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <functional>

using namespace std;

 struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right){}
};

class Tree {
    public: 
    vector<vector<int>> findLeaves(TreeNode* root) {
        vector<vector<int>> leaves;
        if (!root) return leaves;
        
        function<int(TreeNode*)> dfs = [&](TreeNode* node) -> int {
            if (node == nullptr) return -1;
            // Post order travel to find depth of left and right 
            int left_depth = dfs(node->left);
            int right_depth = dfs(node->right);
            // locate the level of current node
            int current_depth = max(left_depth, right_depth) + 1;
            
            // Ensure the result vector has enough space
            if (current_depth >= leaves.size()) {
                leaves.push_back({});
            }
            // Add the current node's value to the corresponding height list
            leaves[current_depth].push_back(node->val);

            // Nullify the leaves 
            if (left_depth == -1) node->left = nullptr;
            if (right_depth == -1) node->right = nullptr;
            return current_depth;
        };          
        dfs(root);
        return leaves;
    }
};

TreeNode* createTree(const vector<int>& vals, int index = 0) {
    if (index >= vals.size() || vals[index] == -1) return nullptr;
    TreeNode* node = new TreeNode(vals[index]);
    node->left = createTree(vals, 2 * index + 1);
    node->right = createTree(vals, 2 * index + 2);
    return node;
}
void printResult(const vector<vector<int>>& result) {
    for (const auto& level : result) {
        cout << "[";
        for (int i = 0; i < level.size(); ++i) {
            cout << level[i];
            if (i < level.size() - 1) cout << ",";
        }
        cout << "] ";
    }
    cout << endl;
}

int main() {
    Tree tree;
    vector<int> vals1 = {1, 2, 3, 4, 5};
    TreeNode* root1 = createTree(vals1);
    vector<vector<int>> result1 = tree.findLeaves(root1);
    printResult(result1);  // Output: [[4,5,3],[2],[1]]

    vector<int> vals2 = {1};
    TreeNode* root2 = createTree(vals2);
    vector<vector<int>> result2 = tree.findLeaves(root2);
    printResult(result2);  // Output: [[1]]

    return 0;
}