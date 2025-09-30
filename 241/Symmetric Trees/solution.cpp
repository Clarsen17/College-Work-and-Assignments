#include "node.h"

// Function to check if two trees are symmetric
bool symmetric(node* t1, node* t2) 
{
    // If both trees are empty, they are symmetric
    if (t1 == nullptr && t2 == nullptr) 
	{
        return true;
    }
    // If one of the trees is empty but not the other, they are not symmetric
    if (t1 == nullptr || t2 == nullptr) 
	{
        return false;
    }
    // Check if the current nodes are symmetric and recursively check the left subtree of t1 with the right subtree of t2 and the right subtree of t1 with the left subtree of t2
    return symmetric(t1->left, t2->right) && symmetric(t1->right, t2->left);
}

