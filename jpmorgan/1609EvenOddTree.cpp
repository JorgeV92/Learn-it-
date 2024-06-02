/*
    1609. Even Odd Tree

    A binary tree is named Even-Odd if it meets the following conditions:
    
        - The root of the binary tree is at level index 0, its children are at level index 1,
        their children are at level index 2, etc

        - For every even-index level, all nodes at the level have odd integer values in stricly 
        increasing order (from left to right)

        - For every odd-index level, all nodes at the level have even integer values in stricly 
        decreasing order (from left to right)

    Given the root of a binary tree, return true if the binary tree is Even-Odd, otherwise return false

    Example 1 

                                                    1
                                                 /    \
                                                10      4
                                                /       / \
                                                3       7   9
                                               / \     /   /
                                              12   8   6   2
*/

#include <iostream>
#include <queue>
#include <climits>
#include <functional>
#include <vector>
#include <optional>


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right; 
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int val) : val(val), left(nullptr), right(nullptr) {}
    TreeNode(int val, TreeNode *left, TreeNode *right) : val(val), left(left), right(right) {}

};

class Graph {
    public:

        TreeNode* createTree(const std::vector<std::optional<int>>& values) {
            if (values.empty() || !values[0].has_value()) return nullptr;

            TreeNode *root = new TreeNode(values[0].value());
            std::queue<TreeNode*> q;
            q.push(root);
            size_t i = 1;

            while (!q.empty() && i < values.size()) {
                TreeNode * node = q.front();
                q.pop();

                if (i < values.size() && values[i].has_value()) {
                    node->left = new TreeNode(values[i].value());
                    q.push(node->left);
                }
                i++;
                if (i < values.size() && values[i].has_value()) {
                    node->right = new TreeNode(values[i].value());
                    q.push(node->right);
                }
                i++;
            } 
            return root;
        }

        bool isEvenOddTree(TreeNode *root) {
            // An empty tree is considered Even-Odd
            if (root == nullptr) return true;

            std::queue<TreeNode*> q;
            q.push(root);
            int level = 0;      // Start with the root level, which is 0

            while (!q.empty()) {
                int size = q.size();
                int prevVal = (level % 2 ==0) ? INT_MIN : INT_MAX;  // Intial values for comparison 

                for (int i = 0; i < size; i++) {
                    TreeNode *node = q.front();
                    q.pop();

                    int val = node->val;

                    // Check if the current level is even indexed
                    if (level % 2 == 0) {
                        // All values must be odd and strictly increasing
                        if (val % 2 == 0 || val <= prevVal) {
                            return false;
                        }
                    } else {
                        // The current level is odd-indexed
                        // All values must be even and strictly decreasing 
                        if (val % 2 != 0 || val >= prevVal) {
                            return false;
                        }
                    }
                    prevVal = val;  // Update prevVal for the next comparison 

                    // Add children to the queue for the next level
                    if (node->left) q.push(node->left);
                    if (node->right) q.push(node->right);
                }
                ++level;    // Move to the next level
            }
            return true;    // If all levels are valid, return true
        }

        void printTreeBFS(TreeNode *root) {
            if (!root) return;

            std::queue<TreeNode*> q;
            q.push(root);
            while (!q.empty()) {
                int size = q.size();
                while (size > 0) {
                    TreeNode *node = q.front();
                    q.pop();
                    if (node) {
                        std::cout << node->val << " ";
                        q.push(node->left);
                        q.push(node->right);
                    } else {
                        std::cout << "null ";
                    }
                    --size;
                }
                std::cout << std::endl;
            }
        } 

};

int main () {

    Graph g;

    std::vector<std::optional<int>> values = {1, 10, 4, 3, std::nullopt, 7, 9, 12, 8, 6, std::nullopt, std::nullopt, 2};
    
    TreeNode *root = g.createTree(values);

    bool isEvenOddTree = g.isEvenOddTree(root);

    std::cout << "Tree structure : \n";
    g.printTreeBFS(root);

    std::cout << "Is the tree Even-Odd? " << (isEvenOddTree ? "True" : "False") << std::endl;

    // Clean up memory
    std::function<void(TreeNode*)> deleteTree = [&](TreeNode *node) {
        if (node == nullptr) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    };

    deleteTree(root);

    return 0;
}