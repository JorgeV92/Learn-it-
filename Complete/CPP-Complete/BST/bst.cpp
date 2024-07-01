#include <iostream>
#include <memory>
#include <vector>
#include "CLI/CLI.hpp" // Include CLI11 header

using namespace std;

struct node {
    int key;
    unique_ptr<node> left;
    unique_ptr<node> right;

    node(int k) : key(k), left(nullptr), right(nullptr) {}
};

// Insert a new node with key k into the BST
unique_ptr<node> insert(unique_ptr<node> root, int k) {
    if (!root) return make_unique<node>(k);
    if (k < root->key) {
        root->left = insert(std::move(root->left), k);
    } else if (k > root->key) {
        root->right = insert(std::move(root->right), k);
    }
    return root;
}

// Search for a node with key k in the BST
node* search(node* root, int k) {
    if (!root || root->key == k) return root;
    if (k < root->key) {
        return search(root->left.get(), k);
    } else {
        return search(root->right.get(), k);
    }
}

// Inorder traversal of the BST
void inorder(const node* root) {
    if (root) {
        inorder(root->left.get());
        cout << root->key << " ";
        inorder(root->right.get());
    }
}

// Find the node with the minimum key in the BST
node* tree_minimum(node* root) {
    while (root && root->left) {
        root = root->left.get();
    }
    return root;
}

// Find the node with the maximum key in the BST
node* tree_maximum(node* root) {
    while (root && root->right) {
        root = root->right.get();
    }
    return root;
}

// Delete a node with key k from the BST
unique_ptr<node> tree_delete(unique_ptr<node> root, int k) {
    if (!root) return nullptr;

    if (k < root->key) {
        root->left = tree_delete(std::move(root->left), k);
    } else if (k > root->key) {
        root->right = tree_delete(std::move(root->right), k);
    } else {
        if (!root->left) {
            return std::move(root->right);
        } else if (!root->right) {
            return std::move(root->left);
        } else {
            node* temp = tree_minimum(root->right.get());
            root->key = temp->key;
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
    cout << endl;

    if (search_value != -1) {
        node* result = search(root.get(), search_value);
        if (result) {
            cout << "Found " << search_value << " in the BST." << endl;
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
