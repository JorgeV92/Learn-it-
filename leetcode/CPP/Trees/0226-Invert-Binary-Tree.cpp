/*
 _______  ______ _______ _______ _______
    |    |_____/ |______ |______ |______
    |    |    \_ |______ |______ ______|
                                       

    0226. Invert Binary Tree    (Easy)

    Given the root of a binary tree, invert the tree, and return its root.

    Example 1:

    Input: root = [4,2,7,1,3,6,9]
    Output: [4,7,2,9,6,3,1]

    Example 2:

    Input: root = [2,1,3]
    Output: [2,3,1]

    Example 3:

    Input: root = []
    Output: []
*/

///////////////////////////////////////////////////////////////////////////////////////////////////////
// Method recursively swap left and right children of every node in the tree. Using the method 
// of depth-first search (DFS) and breadth-first search (BFS) approach. 
///////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <queue>

struct TreeNode {
    int val; 
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left) , right(right) {}
};

class Trees {
    public:
        TreeNode *invertTreeDFS(TreeNode *root) {
            if (!root) {
                return nullptr; // Base case: if the node is null, return null
            }

            // Swap the left and right children
            TreeNode *temp = root->left;
            root->left = root->right;
            root->right = temp;

            // Recursively inver the left and right subtrees
            invertTreeDFS(root->left);
            invertTreeDFS(root->right);

            return root;
        }

        TreeNode *invertTreeBFS(TreeNode *root) {
            if (!root) return nullptr;

            std::queue<TreeNode*> q;
            q.push(root);

            while (!q.empty()) {
                TreeNode *current = q.front(); q.pop();

                // Swap the left and right children 
                TreeNode *temp = current->left;
                current->left = current->right;
                current->right = temp;

                if (current->left) {
                    q.push(current->left);
                } 
                if (current->right) {
                    q.push(current->right);
                }
            }
            return root;
        }

        void printTree(TreeNode *root) {
            if (!root) return;

            std::queue<TreeNode*> q;
            q.push(root);

            while (!q.empty()) {
                TreeNode *current = q.front(); q.pop();

                if (current) {
                    std::cout << current->val << " ";
                    q.push(current->left);
                    q.push(current->right);
                } 
            }
            std::cout << std::endl;
        }
};

int main() { 
    Trees trees;
    
    // Example 1: Input: root = [4,2,7,1,3,6,9]
    TreeNode* root1 = new TreeNode(4);
    root1->left = new TreeNode(2);
    root1->right = new TreeNode(7);
    root1->left->left = new TreeNode(1);
    root1->left->right = new TreeNode(3);
    root1->right->left = new TreeNode(6);
    root1->right->right = new TreeNode(9);

    std::cout << "Original tree 1: ";
    trees.printTree(root1);
    TreeNode* inverted1 = trees.invertTreeBFS(root1);
    std::cout << "Inverted tree 1: ";
   trees.printTree(inverted1);

    // Example 2: Input: root = [2,1,3]
    TreeNode* root2 = new TreeNode(2);
    root2->left = new TreeNode(1);
    root2->right = new TreeNode(3);

    std::cout << "Original tree 2: ";
    trees.printTree(root2);
    TreeNode* inverted2 = trees.invertTreeBFS(root2);
    std::cout << "Inverted tree 2: ";
    trees.printTree(inverted2);

    // Example 3: Input: root = []
    TreeNode* root3 = nullptr;

    std::cout << "Original tree 3: ";
    trees.printTree(root3);
    TreeNode* inverted3 = trees.invertTreeBFS(root3);
    std::cout << "Inverted tree 3: ";
    trees.printTree(inverted3);

    return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
// 1. InvertTree
///////////////////////////////////////////////////////////////////////////////////////////////////////