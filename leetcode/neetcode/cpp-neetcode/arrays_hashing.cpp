#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <stack>
#include <queue>
#include <unordered_map>
#include <functional>

using namespace std;


/////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      Array & Hashing 
/////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////
//                      Contains Duplicat 217
///////////////////////////////////////////////////////////////////
bool hasDuplicate(vector<int>& A) {
    if (A.empty()) return false;
    set<int> ASet(A.begin(), A.end());

    if (A.size() != ASet.size()) return true;
    else return false;
}

///////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////
//                                              END
/////////////////////////////////////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      Two Pointers
/////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
//                      Valid Palindrome
///////////////////////////////////////////////////////////////////
bool isPalindrome(string s) {
    int l = 0, r = s.size() - 1;
    while (l < r) {
        while (!isalnum(s[l]) && l < r) {
            l++;
        }

        while (!isalnum(s[r]) && l < r) {
            r--;
        } 
        if (tolower(s[l] != tolower(s[r]))) {
            return false;
        }
        l++;
        r--;
    }
    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//                                              END
/////////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////////////////////
//                                              Stack 
/////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////
//                      Valid Parentheses
///////////////////////////////////////////////////////////////////
/*
    1.	We iterate over each character in the string s.
	2.	If the character is an open bracket ('(', '{', '['), we push it onto the stack.
	3.	If the character is a close bracket (')', '}', ']'), we check if the stack is empty. If the stack is empty, it means there’s no matching open bracket, so the string is invalid.
	4.	If the stack is not empty, we pop the top element from the stack and check if it matches the current close bracket. If it does not match, the string is invalid.
	5.	After processing all characters, the stack should be empty for the string to be valid. If it’s not empty, it means there are unmatched open brackets.
*/
bool isValid(string s) {
    stack<char> st;
    for (char c : s) {
        if (c == '(' || c == '{' || c == '[') {
            st.push(c);
        } else {
            if (st.empty()) return false;
            char top = st.top(); st.pop();
            if ((c == ')' && top != '(') || 
                (c == '}' && top != '{') || 
                (c == ']' && top != '[')) {
                    return false;
                }
        }
    }
    return st.empty();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//                                              END
/////////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////////////////////
//                                              Binary search 
/////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
//                     Binary search 
///////////////////////////////////////////////////////////////////
int search(vector<int>& A, int t) {
    if (A.empty()) return -1;
    int l = 0, r = A.size() - 1;

    while (l <= r) {
        int m = l + (r - l) / 2;

        if (A[m] == t) {
            return m;
        } else if (A[m] < t) {
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    return -1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//                                              END
/////////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////////////////////
//                                              Sliding Window 
/////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////
//                     Best Time to Buy and Sell Stock 
///////////////////////////////////////////////////////////////////
/*
    1.	Initialize a variable min_price to a very large value to track the minimum price encountered so far.
	2.	Initialize a variable max_profit to 0 to track the maximum profit possible.
	3.	Iterate over each price in the prices array.
	4.	For each price, update min_price to be the minimum of min_price and the current price.
	5.	Calculate the profit by subtracting the current min_price from the current price.
	6.	Update max_profit to be the maximum of max_profit and the calculated profit.
	7.	After iterating through all the prices, max_profit will contain the maximum profit possible.
*/
int maxProfit(vector<int>& prices) {
    int min_price = INT_MAX;
    int max_profit = 0; 

    for (int price : prices) {
        min_price = min(min_price, price);
        int profit = price - min_price;
        max_profit = max(max_profit, profit);
    }
    return max_profit;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//                                              END
/////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////
//                                          Linked List
/////////////////////////////////////////////////////////////////////////////////////////////////////

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

///////////////////////////////////////////////////////////////////
//                     Reversed Linked List 
///////////////////////////////////////////////////////////////////
/*
    1.	Initialize three pointers:
	•	prev to nullptr (this will eventually become the new head of the reversed list).
	•	current to head (this is used to traverse the list).
	•	next to nullptr (this will be used to store the next node temporarily).
	2.	Iterate through the list until current is nullptr:
	•	Store the next node (current->next) in next.
	•	Reverse the current node’s pointer by setting current->next to prev.
	•	Move the prev pointer to the current node.
	•	Move the current pointer to the next node (which was stored in next).
	3.	After the loop, prev will point to the new head of the reversed list.

*/
ListNode* reverseList(ListNode* head) {
    if (head == nullptr || head->next == nullptr) return head;
    ListNode *prev = nullptr;
    ListNode *curr = head;
    ListNode *next = nullptr;

    while (curr != nullptr) {
        next = curr->next;  // Store the next node
        curr->next = prev;  // Reverse the current node's pointer
        prev = curr;        // Move prev to the current node
        curr = next;        // Move to the next node
    }
    return prev;


}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//                                              END
/////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////
//                                              Trees
/////////////////////////////////////////////////////////////////////////////////////////////////////
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

///////////////////////////////////////////////////////////////////
//                     Invert Binary Tree
///////////////////////////////////////////////////////////////////
/*
    1.	If the root is nullptr, return nullptr (base case for the recursion).
	2.	Swap the left and right children of the current node.
	3.	Recursively invert the left subtree.
	4.	Recursively invert the right subtree.
	5.	Return the root after the subtrees have been inverted.
*/
TreeNode* invertTree(TreeNode* root) {
    if (!root) return nullptr;

    TreeNode *temp = root->left;
    root->left = root->right;
    root->right = temp;

    invertTree(root->left);
    invertTree(root->right);

    return root;   
}





/////////////////////////////////////////////////////////////////////////////////////////////////////
//                                              END
/////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////
//                                              Tries
/////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
//                     Implement Trie Prefix Tree
///////////////////////////////////////////////////////////////////

class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;
    }
};

class Trie {
private:
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }
    
    void insert(string word) {
        TrieNode* node = root;
        for (char c : word) {
            if (node->children.find(c) == node->children.end()) {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
        }
        node->isEndOfWord = true;
    }
    
    bool search(string word) {
        TrieNode* node = root;
        for (char c : word) {
            if (node->children.find(c) == node->children.end()) {
                return false;
            }
            node = node->children[c];
        }
        return node->isEndOfWord;
    }
    
    bool startsWith(string prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            if (node->children.find(c) == node->children.end()) {
                return false;
            }
            node = node->children[c];
        }
        return true;
    }
};


/////////////////////////////////////////////////////////////////////////////////////////////////////
//                                              END
/////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////
//                                              Backtracking
/////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
//                     Subsets
///////////////////////////////////////////////////////////////////
/*
    1.	Initialization:
	•	subsets initializes the result vector to store all subsets and the subset vector to store the current subset being constructed.
	2.	Lambda Function:
	•	We define a lambda function backtrack that takes an integer start as an argument.
	•	The lambda function adds the current subset to the result.
	•	It iterates through the elements starting from the current index start.
	•	For each element, it includes the element in the subset and recursively calls backtrack for the next index.
	•	After returning from the recursion, it removes the last element from subset to explore other subsets without the current element.
	3.	Start the Backtracking:
	•	We call the lambda function backtrack starting from index 0 to generate all possible subsets.
*/
vector<vector<int>> subsets(vector<int>& A) {
    vector<vector<int>> result;
    vector<int> subset;

    function<void(int)> backtrack = [&](int start) {
        result.push_back(subset);
        for (int i = start; i < A.size(); i++) {
            subset.push_back(A[i]);
            backtrack(i + 1);
            subset.pop_back();
        }
    };
    backtrack(0);
    return result;
}
/*
Let’s work through the example A = [1, 2, 3].

	1.	Initial Call:
	•	backtrack(0) is called.
	•	result starts as an empty list: result = [].
	•	subset starts as an empty list: subset = [].
	2.	First Level of Recursion:
	•	backtrack(0):
	•	subset is [], so result becomes [[]].
	•	Loop iteration i = 0:
	•	Add nums[0] (which is 1) to subset: subset = [1].
	•	Call backtrack(1).
	3.	Second Level of Recursion:
	•	backtrack(1):
	•	subset is [1], so result becomes [[], [1]].
	•	Loop iteration i = 1:
	•	Add nums[1] (which is 2) to subset: subset = [1, 2].
	•	Call backtrack(2).
	4.	Third Level of Recursion:
	•	backtrack(2):
	•	subset is [1, 2], so result becomes [[], [1], [1, 2]].
	•	Loop iteration i = 2:
	•	Add nums[2] (which is 3) to subset: subset = [1, 2, 3].
	•	Call backtrack(3).
	5.	Base Case:
	•	backtrack(3):
	•	subset is [1, 2, 3], so result becomes [[], [1], [1, 2], [1, 2, 3]].
	•	Since start is now 3 (equal to the length of nums), it returns.
	•	Backtrack: Remove 3 from subset: subset = [1, 2].
	6.	Continuing Second Level of Recursion:
	•	backtrack(2):
	•	Loop iteration i = 2 ends.
	•	Backtrack: Remove 2 from subset: subset = [1].
	•	Loop iteration i = 1 ends.
	•	Loop iteration i = 2:
	•	Add nums[2] (which is 3) to subset: subset = [1, 3].
	•	Call backtrack(3).
	7.	Base Case:
	•	backtrack(3):
	•	subset is [1, 3], so result becomes [[], [1], [1, 2], [1, 2, 3], [1, 3]].
	•	Backtrack: Remove 3 from subset: subset = [1].
	•	Loop iteration i = 2 ends.
	•	Backtrack: Remove 1 from subset: subset = [].
	8.	First Level of Recursion:
	•	backtrack(0):
	•	Loop iteration i = 0 ends.
	•	Loop iteration i = 1:
	•	Add nums[1] (which is 2) to subset: subset = [2].
	•	Call backtrack(2).
	9.	Second Level of Recursion:
	•	backtrack(2):
	•	subset is [2], so result becomes [[], [1], [1, 2], [1, 2, 3], [1, 3], [2]].
	•	Loop iteration i = 2:
	•	Add nums[2] (which is 3) to subset: subset = [2, 3].
	•	Call backtrack(3).
	10.	Base Case:
	•	backtrack(3):
	•	subset is [2, 3], so result becomes [[], [1], [1, 2], [1, 2, 3], [1, 3], [2], [2, 3]].
	•	Backtrack: Remove 3 from subset: subset = [2].
	•	Loop iteration i = 2 ends.
	•	Backtrack: Remove 2 from subset: subset = [].
	11.	First Level of Recursion:
	•	backtrack(0):
	•	Loop iteration i = 1 ends.
	•	Loop iteration i = 2:
	•	Add nums[2] (which is 3) to subset: subset = [3].
	•	Call backtrack(3).
	12.	Base Case:
	•	backtrack(3):
	•	subset is [3], so result becomes [[], [1], [1, 2], [1, 2, 3], [1, 3], [2], [2, 3], [3]].
	•	Backtrack: Remove 3 from subset: subset = [].
	•	Loop iteration i = 2 ends.

    result = [[], [1], [1, 2], [1, 2, 3], [1, 3], [2], [2, 3], [3]]
*/


/////////////////////////////////////////////////////////////////////////////////////////////////////
//                                              END
/////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////
//                                       Heap / Priority Queue
/////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
//               Kth Largest Element in a Stream 
///////////////////////////////////////////////////////////////////
class KthLargest {
private:
    priority_queue<int, vector<int>, greater<int>> minHeap;
    int k; // k largest elemets 
public:
    KthLargest(int k, vector<int>& A) {
        this->k = k;
        for (int num : A) {
            add(num);
        }
    }
    
    int add(int val) {
        if (minHeap.size() < k) {
            minHeap.push(val);
        } else if (val > minHeap.top()) {
            minHeap.pop();
            minHeap.push(val);
        }
        return minHeap.top();
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////
//                                              END
/////////////////////////////////////////////////////////////////////////////////////////////////////







typedef struct {
    bool array_hashing;
    bool two_pointer;
    bool stack;
    bool sliding_window;
    bool linked_list;
    bool trees;
    bool tries;
    bool backtracking;
} AlgorithmFlags;
