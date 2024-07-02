import argparse

class Node:
    def __init__(self, key):
        self.key = key
        self.left = None
        self.right = None

class BST:
    def __init__(self):
        self.root = None

    def insert(self, root, key):
        if not root:
            return Node(key)
        if key < root.key:
            root.left = self.insert(root.left, key)
        else:
            root.right = self.insert(root.right, key)
        return root

    def search(self, root, key):
        if not root or root.key == key:
            return root
        if key < root.key:
            return self.search(root.left, key)
        else:
            return self.search(root.right, key)

    def inorder(self, root):
        if root:
            self.inorder(root.left)
            print(root.key, end=" ")
            self.inorder(root.right)

    def tree_minimum(self, root):
        while root and root.left:
            root = root.left
        return root

    def tree_delete(self, root, key):
        if not root:
            return None
        if key < root.key:
            root.left = self.tree_delete(root.left, key)
        elif key > root.key:
            root.right = self.tree_delete(root.right, key)
        else:
            if not root.left:
                return root.right
            elif not root.right:
                return root.left
            temp = self.tree_minimum(root.right)
            root.key = temp.key
            root.right = self.tree_delete(root.right, temp.key)
        return root

def main():
    parser = argparse.ArgumentParser(description="BST Program")
    parser.add_argument('-i', '--insert', nargs='+', type=int, help="Values to insert into the BST")
    parser.add_argument('-s', '--search', type=int, help="Value to search in the BST")
    parser.add_argument('-d', '--delete', type=int, help="Value to delete from the BST")
    args = parser.parse_args()

    bst = BST()
    root = None

    if args.insert:
        for value in args.insert:
            root = bst.insert(root, value)

    print("Inorder traversal after insertions: ", end="")
    bst.inorder(root)
    print()

    if args.search is not None:
        result = bst.search(root, args.search)
        if result:
            print(f"Found {args.search} in the BST.")
        else:
            print(f"{args.search} not found in the BST.")

    if args.delete is not None:
        root = bst.tree_delete(root, args.delete)
        print("Inorder traversal after deletion: ", end="")
        bst.inorder(root)
        print()

if __name__ == "__main__":
    main()