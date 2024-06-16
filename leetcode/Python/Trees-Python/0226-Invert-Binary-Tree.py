'''
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
'''

#################################################################################
# Method recursively swap left and right children of every node in the tree. Using the method 
# of depth-first search (DFS) and breadth-first search (BFS) approach. 
#################################################################################

from collections import deque
from typing import Optional, Deque

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
        
class Trees:
    def invertTreeDFS(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        if not root:
            return None 
        
        # Swap the left and right children
        root.left, root.right = root.right, root.left
        
        # Recurse
        self.invertTreesDFS(root.left)
        self.invertTreesDFS(root.right)
        
        return root
    
    def invertTreeBFS(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        if not root:
            return None
        
        q: Deque[TreeNode] = deque([root])
        
        while q:
            current = q.popleft()
            
            # Swap
            current.left, current.right = current.right, current.left
            
            if current.left:
                q.append(current.left)
            if current.right:
                q.append(current.right)
                
        return root
    
    def printTree(self, root: Optional[TreeNode]) -> None:
        if not root:
            return None
        
        q: Deque[Optional[TreeNode]] = deque([root])
        
        while q:
            current = q.popleft()
            
            if current:
                print(current.val, end=" ")
                q.append(current.left)
                q.append(current.right)
                
        print()
            
if __name__ == "__main__":
    trees = Trees()
    
    # Example 1: Input: root = [4,2,7,1,3,6,9]
    root1 = TreeNode(4)
    root1.left = TreeNode(2)
    root1.right = TreeNode(7)
    root1.left.left = TreeNode(1)
    root1.left.right = TreeNode(3)
    root1.right.left = TreeNode(6)
    root1.right.right = TreeNode(9)

    print("Original tree 1: ", end="")
    trees.printTree(root1)
    inverted1 = trees.invertTreeBFS(root1)
    print("Inverted tree 1: ", end="")
    trees.printTree(inverted1)

    # Example 2: Input: root = [2,1,3]
    root2 = TreeNode(2)
    root2.left = TreeNode(1)
    root2.right = TreeNode(3)

    print("Original tree 2: ", end="")
    trees.printTree(root2)
    inverted2 = trees.invertTreeBFS(root2)
    print("Inverted tree 2: ", end="")
    trees.printTree(inverted2)

    # Example 3: Input: root = []
    root3 = None

    print("Original tree 3: ", end="")
    trees.printTree(root3)
    inverted3 = trees.invertTreeBFS(root3)
    print("Inverted tree 3: ", end="")
    trees.printTree(inverted3)
    
#################################################################################
# 1. InvertTree
#################################################################################