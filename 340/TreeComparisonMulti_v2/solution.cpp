// Collen Larsen Z1930118
// CSCI 340-L2 "TreeComparisonMulti_v2"
#include "treenode.h"
#include <iostream>
#include <queue>
#include <utility> 
#include <algorithm>

using namespace std;


// Function to check if two trees are the same;
bool isSameTree(TreeNode* p, TreeNode* q) 
{
    if (!p && !q) return true; // Both trees are empty
    if (!p || !q || p->value != q->value) return false; // One tree is empty or values mismatch
    return isSameTree(p->left, q->left) && isSameTree(p->right, q->right); // Recursive check
}

// Function to check if two trees are symmetric
bool isSymmetricTree(TreeNode* p, TreeNode* q) 
{
    if (!p && !q) return true; // Both trees are empty
    if (!p || !q || p->value != q->value) return false; // One tree is empty or values mismatch
    return isSymmetricTree(p->left, q->right) && isSymmetricTree(p->right, q->left); // Mirror check
}

// Helper function to check if one tree is a subtree of another
bool isSubtree(TreeNode* s, TreeNode* t) 
{
    if (!s) return false; // Base case: reached end of tree s without finding subtree
    if (isSameTree(s, t)) return true; // Check if current subtree is identical to t
    return isSubtree(s->left, t) || isSubtree(s->right, t); // Recursive check
}

// Function to check if one tree is a subtree of another
bool isOneTreePartOfAnother(TreeNode* p, TreeNode* q) 
{
    if (!p || !q) return false; // Either tree is empty
    return isSubtree(p, q); // Simply check if q is a sub of p
}

// Function to check if a tree satisfies the max-heap property
bool isMaxHeap(TreeNode* root) 
{
    if (!root) return true; // An empty tree is a valid max-heap
    queue<TreeNode*> q;
    q.push(root);
    bool nullEncountered = false; // Flag to detect completeness property violations
    
    while (!q.empty()) 
	{
        TreeNode* node = q.front();
        q.pop();

        if (node->left) 
		{
            if (nullEncountered || node->value < node->left->value) return false;
            q.push(node->left);
        } 
		else 
		{
            nullEncountered = true;
        }

        if (node->right) 
		{
            if (nullEncountered || node->value < node->right->value) return false;
            q.push(node->right);
        }
		 else 
		{
            nullEncountered = true;
        }
    }
    return true;
}

// Function to check if two trees are the same heap
bool isSameHeap(TreeNode* p, TreeNode* q) 
{
    if (!isSameTree(p, q)) return false; // Trees must be identical in structure and values
    return isMaxHeap(p) && isMaxHeap(q); // Both trees must satisfy max-heap property
}

// Function to calculate the maximum width of a binary tree
int calculateWidth(TreeNode* root) 
{
    if (!root) return 0; // Width of an empty tree is 0

    queue<pair<TreeNode*, int>> q;
    q.push(make_pair(root, 0)); // Root node at position 0

    int maxWidth = 0;

    while (!q.empty()) 
	{
        int size = q.size();
        int minIndex = q.front().second;
        int first = 0, last = 0;

        for (int i = 0; i < size; i++) 
		{
            pair<TreeNode*, int> current = q.front(); // Extract the pair from the queue
            TreeNode* node = current.first;
            int index = current.second;
            q.pop();

            index -= minIndex; // Normalize index to avoid overflow

            if (i == 0) first = index; // Capture the first position at this level
            if (i == size - 1) last = index; // Capture the last position at this level

            // Push children into the queue with updated position
            if (node->left) q.push(make_pair(node->left, 2 * index + 1));
            if (node->right) q.push(make_pair(node->right, 2 * index + 2));
        }

        maxWidth = max(maxWidth, last - first + 1); // Update maximum width
    }

    return maxWidth;
}

// Function to check if two trees have the same width
bool ofSameWidth(TreeNode* p, TreeNode* q) 
{
    return calculateWidth(p) == calculateWidth(q); // Compare widths of both trees
}

