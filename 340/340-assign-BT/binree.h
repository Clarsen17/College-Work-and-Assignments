// Collen Larsen Z2930118
// CSCI 340-3 
// bintree.h

#ifndef NIU_CSCI330_BINTREE_IMPL_H
#define NIU_CSCI330_BINTREE_IMPL_H

#include "bintree.decl.h"
#include <vector>
#include <queue>

// Pre-order traversal
template <typename BINTREENODE, typename FN>
void preorder(BINTREENODE *root, FN fn) {
    if (root) {
        fn(root);
        preorder(root->left, fn);
        preorder(root->right, fn);
    }
}

// In-order traversal
template <typename BINTREENODE, typename FN>
void inorder(BINTREENODE *root, FN fn) {
    if (root) {
        inorder(root->left, fn);
        fn(root);
        inorder(root->right, fn);
    }
}

// Post-order traversal
template <typename BINTREENODE, typename FN>
void postorder(BINTREENODE *root, FN fn) {
    if (root) {
        postorder(root->left, fn);
        postorder(root->right, fn);
        fn(root);
    }
}

// Level-order traversal
template <typename BINTREENODE, typename FN>
void levelorder(BINTREENODE *root, FN fn) {
    if (!root) return;
    std::queue<BINTREENODE*> queue;
    queue.push(root);
    while (!queue.empty()) {
        BINTREENODE* node = queue.front();
        queue.pop();
        fn(node);
        if (node->left)  queue.push(node->left);
        if (node->right) queue.push(node->right);
    }
}

// Delete tree
template <typename BINTREENODE>
void delete_tree(BINTREENODE * &node) {
    if (node) {
        delete_tree(node->left);
        delete_tree(node->right);
        delete node;
        node = nullptr;
    }
}

// Tilted tree functions

// Get all children (first child via left, siblings via right)
template <typename BINTREENODE>
std::vector<BINTREENODE*> tilted_get_children(BINTREENODE *node) {
    std::vector<BINTREENODE*> children;
    if (node) {
        BINTREENODE *child = node->left;
        while (child) {
            children.push_back(child);
            child = child->right;
        }
    }
    return children;
}

// Find the true tilted parent.
// Key detail: if node is actually a "right sibling," you must keep going up.
template <typename BINTREENODE>
BINTREENODE* tilted_find_parent(BINTREENODE* node) {
    if (!node || !node->parent) return nullptr; // If no parent, done.

    BINTREENODE* current = node->parent;
    // Keep climbing while node is a right-sibling child
    while (current && current->right == node) {
        node    = current;       // move up one level
        current = current->parent;
    }
    return current; // may be nullptr if we climbed to the root
}

// Tilted level-order traversal
template <typename BINTREENODE, typename FN>
void tilted_levelorder(BINTREENODE *root, FN fn) {
    if (!root) return;
    std::queue<BINTREENODE*> queue;
    queue.push(root);
    while (!queue.empty()) {
        BINTREENODE *node = queue.front();
        queue.pop();
        fn(node);
        // Enqueue all children (the "left" chain), then siblings on the "right".
        // We already have a helper to get them:
        for (BINTREENODE *child : tilted_get_children(node)) {
            queue.push(child);
        }
    }
}

#endif

