/*
 _______  ______ _______ _______ _______
    |    |_____/ |______ |______ |______
    |    |    \_ |______ |______ ______|
                                       
    0104. Maximum Depth of Binary Tree      (Easy)

    Given the root of a binary tree, return its maximum depth.

    A binary tree's maximum depth is the number of nodes along the longest path from the root node 
    down to the farthest leaf node.

    Example 1:

    Input: root = [3,9,20,null,null,15,7]
    Output: 3

    3
   / \
  9  20
     /  \
    15   7


    Example 2:

    Input: root = [1,null,2]
    Output: 2

*/



#include <iostream>
#include <memory>

struct TreeNode {
    int val; 
    std::shared_ptr<TreeNode> left;
    std::shared_ptr<TreeNode> right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, std::shared_ptr<TreeNode> left, std::shared_ptr<TreeNode> right) : val(x), left(left) , right(right) {}
};


class Trees {
    public:
        int maxDepth(std::shared_ptr<TreeNode> root) {
            if (root == nullptr) return 0;
            int leftDepth = maxDepth(root->left);
            int rightDepth = maxDepth(root->right);
            return std::max(leftDepth, rightDepth) + 1;
        }
};

int main() {
    // Example usage:
    std::shared_ptr<TreeNode> root = std::make_shared<TreeNode>(3);
    root->left = std::make_shared<TreeNode>(9);
    root->right = std::make_shared<TreeNode>(20);
    root->right->left = std::make_shared<TreeNode>(15);
    root->right->right = std::make_shared<TreeNode>(7);

    Trees tree;
    int depth = tree.maxDepth(root);
    std::cout << "Maximum depth of the binary tree is: " << depth << std::endl;

    return 0;
}