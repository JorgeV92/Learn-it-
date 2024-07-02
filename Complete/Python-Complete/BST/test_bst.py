import unittest
from io import StringIO
import sys

# Import the BST and Node classes from your BST implementation file
from bst import BST, Node

class TestBST(unittest.TestCase):
    def setUp(self):
        self.bst = BST()
        self.root = None

    def test_insert(self):
        values = [10, 5, 15, 2, 7, 12, 20]
        for value in values:
            self.root = self.bst.insert(self.root, value)
        
        expected_inorder = "2 5 7 10 12 15 20 "
        captured_output = StringIO()
        sys.stdout = captured_output
        self.bst.inorder(self.root)
        sys.stdout = sys.__stdout__

        self.assertEqual(captured_output.getvalue(), expected_inorder)

    def test_search(self):
        values = [10, 5, 15, 2, 7, 12, 20]
        for value in values:
            self.root = self.bst.insert(self.root, value)
        
        self.assertIsNotNone(self.bst.search(self.root, 10))
        self.assertIsNotNone(self.bst.search(self.root, 2))
        self.assertIsNotNone(self.bst.search(self.root, 20))
        self.assertIsNone(self.bst.search(self.root, 100))

    def test_delete(self):
        values = [10, 5, 15, 2, 7, 12, 20]
        for value in values:
            self.root = self.bst.insert(self.root, value)

        self.root = self.bst.tree_delete(self.root, 10)
        expected_inorder = "2 5 7 12 15 20 "
        captured_output = StringIO()
        sys.stdout = captured_output
        self.bst.inorder(self.root)
        sys.stdout = sys.__stdout__

        self.assertEqual(captured_output.getvalue(), expected_inorder)

        self.root = self.bst.tree_delete(self.root, 2)
        expected_inorder = "5 7 12 15 20 "
        captured_output = StringIO()
        sys.stdout = captured_output
        self.bst.inorder(self.root)
        sys.stdout = sys.__stdout__

        self.assertEqual(captured_output.getvalue(), expected_inorder)

if __name__ == '__main__':
    unittest.main()