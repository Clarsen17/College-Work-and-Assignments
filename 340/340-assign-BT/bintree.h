/// Collen Larsen Z1930118
/// CSCI 340-3
/// April 4th 2025
// Bintree.h

#ifndef NIU_CSCI330_BINTREE_IMPL_H
#define NIU_CSCI330_BINTREE_IMPL_H

#include "bintree.decl.h"
#include <queue>
#include <vector>

/**
 * @brief Performs a preorder traversal on a binary tree.
 * @param root Pointer to the root node of the tree.
 * @param fn Function to call on each visited node.
 */
template <typename BINTREENODE, typename FN>
void preorder(BINTREENODE *root, FN fn)
 {
    if (root == nullptr) return;
    fn(root);
    preorder(root->left, fn);
    preorder(root->right, fn);
}

/**
 * @brief Performs an inorder traversal on a binary tree.
 * @param root Pointer to the root node of the tree.
 * @param fn Function to call on each visited node.
 */
template <typename BINTREENODE, typename FN>
void inorder(BINTREENODE *root, FN fn) 
{
    if (root == nullptr) return;
    inorder(root->left, fn);
    fn(root);
    inorder(root->right, fn);
}

/**
 * @brief Performs a postorder traversal on a binary tree.
 * @param root Pointer to the root node of the tree.
 * @param fn Function to call on each visited node.
 */
template <typename BINTREENODE, typename FN>
void postorder(BINTREENODE *root, FN fn)
 {
    if (root == nullptr) return;
    postorder(root->left, fn);
    postorder(root->right, fn);
    fn(root);
}

/**
 * @brief Performs a level-order traversal on a binary tree.
 * @param root Pointer to the root node of the tree.
 * @param fn Function to call on each visited node.
 */
template <typename BINTREENODE, typename FN>
void levelorder(BINTREENODE *root, FN fn) 
{
    if (root == nullptr) return;
    std::queue<BINTREENODE *> queue;
    queue.push(root);
    while (!queue.empty()) 
	{
        BINTREENODE *current = queue.front();
        queue.pop();
        fn(current);
        if (current->left) queue.push(current->left);
        if (current->right) queue.push(current->right);
    }
}

/**
 * @brief Deletes all nodes in the tree, freeing up memory.
 * @param node Reference to the pointer to the root node of the tree.
 */
template <typename BINTREENODE>
void delete_tree(BINTREENODE *&node) 
{
    if (node == nullptr) return;
    delete_tree(node->left);
    delete_tree(node->right);
    delete node;
    node = nullptr;
}

/**
 * @brief Retrieves the direct children of a node in a tilted tree.
 * @param node Pointer to the node whose children are to be gathered.
 * @return A vector containing pointers to the child nodes.
 */
template <typename BINTREENODE>
std::vector<BINTREENODE *> tilted_get_children(BINTREENODE *node) 
{
    std::vector<BINTREENODE *> children;
    if (node == nullptr) return children;
    BINTREENODE *child = node->left;
    while (child != nullptr)
	 {
        children.push_back(child);
        child = child->right;
    }
    return children;
}

/**
 * @brief Finds the parent of a node in a tilted tree.
 * @param node Pointer to the node whose parent is to be found.
 * @return Pointer to the parent node, or nullptr if no parent exists.
 */
template <typename BINTREENODE>
BINTREENODE *tilted_find_parent(BINTREENODE *node) 
{
    if (node == nullptr || node->parent == nullptr) return nullptr;
    if (node->parent->left == node || node->parent->right == node) return node->parent;
    return nullptr;
}

/**
 * @brief Performs a level-order traversal on a tilted tree.
 * @param root Pointer to the root node of the tilted tree.
 * @param fn Function to call on each visited node.
 */
template <typename BINTREENODE, typename FN>
void tilted_levelorder(BINTREENODE *root, FN fn) 
{
    if (root == nullptr) return;
    std::queue<BINTREENODE *> queue;
    queue.push(root);
    while (!queue.empty()) 
	{
        BINTREENODE *current = queue.front();
        queue.pop();
        fn(current);
        std::vector<BINTREENODE *> children = tilted_get_children(current);
        for (BINTREENODE *child : children)  
		{
            queue.push(child);
        }
    }
}

#endif // NIU_CSCI330_BINTREE_IMPL_H

