/*
 _______  ______ _______ _______ _______
    |    |_____/ |______ |______ |______
    |    |    \_ |______ |______ ______|
                                       

    0124. Binary Tree Maximum Path Sum  (Hard)

    A path in a binary tree is a sequence of nodes where each pair of adjacent nodes in the sequence
    has an edge connecting them. A node can only appear in the sequence at most once. Note that the 
    path does not need to pass through the root.

    The path sum of a path is the sum of the node's values in the path.

    Given the root of a binary tree, return the maximum path sum of any non-empty path.


    Example 1:

    Input: root = [1,2,3]
    Output: 6
    Explanation: The optimal path is 2 -> 1 -> 3 with a path sum of 2 + 1 + 3 = 6.

    Example 2:

    Input: root = [-10,9,20,null,null,15,7]
    Output: 42
    Explanation: The optimal path is 15 -> 20 -> 7 with a path sum of 15 + 20 + 7 = 42.
*/

#include <iostream>
#include <memory>
#include <algorithm>
#include <climits>
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
        int maxPathSum(std::shared_ptr<TreeNode> root) {
            int max_sum = INT_MIN;

            std::function<int(std::shared_ptr<TreeNode>)> maxPathSumDFS = [&](std::shared_ptr<TreeNode> node) -> int {
                if (!node) return 0;

                // DFS on the left and right 
                int left_sum = std::max(maxPathSumDFS(node->left), 0);
                int right_sum = std::max(maxPathSumDFS(node->right), 0);

                // calculate the maximum path sum for the current node
                int current_path_sum = node->val + left_sum + right_sum;
                max_sum = std::max(max_sum, current_path_sum);

                return node->val + std::max(left_sum, right_sum);
            };
            maxPathSumDFS(root);
            return max_sum;
        }
};
int main() {
    // Example 1
    auto root1 = std::make_shared<TreeNode>(1);
    root1->left = std::make_shared<TreeNode>(2);
    root1->right = std::make_shared<TreeNode>(3);
    Tree tree1;
    std::cout << "Max Path Sum (Example 1): " << tree1.maxPathSum(root1) << std::endl; // Output: 6

    // Example 2
    auto root2 = std::make_shared<TreeNode>(-10);
    root2->left = std::make_shared<TreeNode>(9);
    root2->right = std::make_shared<TreeNode>(20);
    root2->right->left = std::make_shared<TreeNode>(15);
    root2->right->right = std::make_shared<TreeNode>(7);
    Tree tree2;
    std::cout << "Max Path Sum (Example 2): " << tree2.maxPathSum(root2) << std::endl; // Output: 42

    return 0;
}