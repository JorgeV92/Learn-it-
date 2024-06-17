/*
 _______  ______ _______ _______ _______
    |    |_____/ |______ |______ |______
    |    |    \_ |______ |______ ______|
                                       

    0543. Diameter of Binary Tree      (Easy)

    Given the root of a binary tree, return the length of the diameter of the tree.

    The diameter of a binary tree is the length of the longest path between any two nodes in a tree.
    This path may or may not pass through the root.

    The length of a path between two nodes is represented by the number of edges between them.

    Example 1:


    Input: root = [1,2,3,4,5]
    Output: 3
    Explanation: 3 is the length of the path [4,2,1,3] or [5,2,1,3].


    Example 2:

    Input: root = [1,2]
    Output: 1
*/


#include <iostream>
#include <memory>
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
        int diameterOfBinaryTree(std::shared_ptr<TreeNode> root) {
            int diameter = 0;

            std::function<int(std::shared_ptr<TreeNode>)> maxDepth = [&](std::shared_ptr<TreeNode> node) -> int {
                if (!node) return 0;
                int leftDepth = maxDepth(node->left);
                int rightDepth = maxDepth(node->right);
                diameter = std::max(diameter, leftDepth + rightDepth);
                return std::max(leftDepth, rightDepth) + 1;
            };
            maxDepth(root);
            return diameter;
        }
};

int main() {
    // Example usage:
    auto root = std::make_shared<TreeNode>(1);
    root->left = std::make_shared<TreeNode>(2);
    root->right = std::make_shared<TreeNode>(3);
    root->left->left = std::make_shared<TreeNode>(4);
    root->left->right = std::make_shared<TreeNode>(5);

    Tree tree;
    int diameter = tree.diameterOfBinaryTree(root);
    std::cout << "Diameter of the binary tree is: " << diameter << std::endl;

    return 0;
}