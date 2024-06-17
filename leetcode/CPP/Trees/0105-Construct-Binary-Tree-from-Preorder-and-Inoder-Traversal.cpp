/*
 _______  ______ _______ _______ _______
    |    |_____/ |______ |______ |______
    |    |    \_ |______ |______ ______|
                                       

    0105. Construct Binary Tree from Preorder and Inorder Traversal     (Medium)

    Given two integer arrays preorder and inorder where preorder is the preorder traversal of a 
    binary tree and inorder is the inorder traversal of the same tree, construct and return the binary 
    tree.


    Example 1:

    Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
    Output: [3,9,20,null,null,15,7]


    Example 2:

    Input: preorder = [-1], inorder = [-1]
    Output: [-1]

*/

#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>
#include <functional>

struct TreeNode {
    int val; 
    std::shared_ptr<TreeNode> left;
    std::shared_ptr<TreeNode> right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, std::shared_ptr<TreeNode> left, std::shared_ptr<TreeNode> right) : val(x), left(left) , right(right) {}
};

class Tree {
    public:
        std::shared_ptr<TreeNode> buildTree(std::vector<int>& preorder, std::vector<int>& indorder) {
            std::unordered_map<int, int> inorderIndexMap;
            for (int i = 0; i < indorder.size(); i++) {
                inorderIndexMap[indorder[i]] = i;
            }
            int preorderIndex = 0;

            std::function<std::shared_ptr<TreeNode>(int, int)> buildTreeHelper = [&](int inorderStart, int inorderEnd) -> std::shared_ptr<TreeNode> {
                if (inorderStart > inorderEnd) return nullptr;

                int rootVal = preorder[preorderIndex++];
                auto root = std::make_shared<TreeNode>(rootVal);

                root->left = buildTreeHelper(inorderStart, inorderIndexMap[rootVal] - 1);
                root->right = buildTreeHelper(inorderIndexMap[rootVal] + 1, inorderEnd);

                return root;
            };

            return buildTreeHelper(0, indorder.size() - 1);
        }
};

void printTree(const std::shared_ptr<TreeNode>& root) {
    if (root == nullptr) return;
    std::cout << root->val << " ";
    printTree(root->left);
    printTree(root->right);
}

int main() {
    // Example usage:
    Tree tree;
    std::vector<int> preorder = {3, 9, 20, 15, 7};
    std::vector<int> inorder = {9, 3, 15, 20, 7};

    std::shared_ptr<TreeNode> root = tree.buildTree(preorder, inorder);
    printTree(root);
    std::cout << std::endl;

    return 0;
}