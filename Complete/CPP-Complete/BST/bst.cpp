#include <iostream> 
#include <memory>
#include <vector>
#include "CLI/CLI.hpp"

using namespace std;

struct node {
    int key;
    unique_ptr<node> left;
    unique_ptr<node> right;

    node(int k) : key(k), left(nullptr), right(nullptr) {}
};


unique_ptr<node>  insert(unique_ptr<node>  root, int k) {
    if (!root) return make_unique<node>(k);
    if (k < root->key) {
        root->left = insert(std::move(root->left), k);
    } else if (k > root->key) {
        root->right = insert(std::move(root->right), k);
    }

    return root;
}

node* search(node* root, int k) {
    if (!root || root->key == k) return root;
    if (k < root->key) {
        return search(root->left.get(), k);
    } else {
        return search(root->right.get(), k);
    }
}

void inorder(const node* root) {
    if (root) {
        inorder(root->left.get());
        cout << root->key << " ";
        inorder(root->right.get()); 
    }
}

node* tree_minimum(node* root) {
    while (root && root->left) {
        root = root->left.get();
    }
    return root;
}

struct node* tree_maximum(struct node* root) {
    while (root && root->right) {
        root = root->right.get();
    }
    return root;
}

unique_ptr<node> tree_delete(unique_ptr<node>  root, int k) {
    if (!root) return nullptr;

    if (k < root->key) {
        // Transfer ownership of root->left to the recursive call 
        root->left = tree_delete(std::move(root->left), k);
    } else if (k > root->key) {
        // Transfer ownership of root->right to the recursive call 
        root->right = tree_delete(std::move(root->right), k);
    } else {
        // Node to be deleted is found 
        if (!root->left) {
            // If no left child, return the right subtree, transferring ownership
            return std::move(root->right);
        } else if (!root->right) {
            // If no right child, return the left subtree, transferring ownershi[] 
            return std::move(root->left);
        } else {
            // Node with two children: Get the minimum node from the right subtree
            node* temp = tree_minimum(root->right.get());
            root->key = temp->key;
            // Delete the inorder successor 
            root->right = tree_delete(std::move(root->right), temp->key);
        }
    }
    return root;
}

int main(int argc, char** argv) {
    CLI::App app{"BST Program"};

    vector<int> insert_values;
    int search_value = -1;
    int delete_value = -1;

    app.add_option("-i,--insert", insert_values, "Values to insert into the BST");
    app.add_option("-s,--search", search_value, "Value to search in the BST");
    app.add_option("-d,--delete", delete_value, "Value to delete from the BST");

    CLI11_PARSE(app, argc, argv);

    unique_ptr<node> root = nullptr;
    for (int value : insert_values) {
        root = insert(std::move(root), value);
    }

    cout << "Inorder traversal after insertions: ";
    inorder(root.get());

    if (search_value != -1) {
        node* result = search(root.get(), search_value);
        if (result) {
            cout << endl << "Found " << search_value << " in the BST." << endl;
        } else {
            cout << search_value << " not found in the BST." << endl;
        }
    }

    if (delete_value != -1) {
        root = tree_delete(std::move(root), delete_value);
        cout << "Inorder traversal after deletion: ";
        inorder(root.get());
        cout << endl;
    }

    return 0;
}