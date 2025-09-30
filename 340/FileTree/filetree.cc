// Collen Larsen z1930118
// CSCI 340-3L
// SystemFileTree
// filetree.cc
#include "filetree.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <memory>
#include <algorithm>
#include <climits>  // Fix for INT_MAX

using std::istream;
using std::string;
using std::vector;
using std::unordered_map;
using std::shared_ptr;
using std::make_shared;
using std::cout;
using std::endl;

// Node class for representing files and directories
class Node {
public:
    string name;
    int size;
    bool isDirectory;
    Node* parent;
    unordered_map<string, shared_ptr<Node>> children;

    // Fix the order of initialization to match declaration order
    Node(string name, bool isDirectory, Node* parent = nullptr, int size = 0) 
        : name(name), size(size), isDirectory(isDirectory), parent(parent) {}
};

// Function to read input and build the filesystem tree
shared_ptr<Node> readInput(istream& is) {
    string line;
    shared_ptr<Node> root = make_shared<Node>("/", true);
    Node* current = root.get();

    while (getline(is, line)) {
        std::istringstream ss(line);
        string cmd;
        ss >> cmd;

        if (cmd == "$") {
            ss >> cmd;
            if (cmd == "cd") {
                string path;
                ss >> path;
                if (path == "/") {
                    current = root.get();
                } else if (path == "..") {
                    if (current->parent) current = current->parent;
                } else {
                    if (current->children.count(path))
                        current = current->children[path].get();
                }
            } else if (cmd == "ls") {
                // Do nothing, next lines will be listing files
            }
        } else {
            int size;
            string filename;
            size = std::stoi(cmd);
            ss >> filename;
            bool isDir = filename.back() == '/';
            if (isDir) filename.pop_back(); // Remove '/' from directory names

            auto node = make_shared<Node>(filename, isDir, current, isDir ? 0 : size);
            current->children[filename] = node;
        }
    }
    return root;
}

// Helper function to print the tree structure
void printNode(Node* node, int level = 0) {
    if (level == 0) {
        cout << "()";  // No extra newline
    } else {
        for (int i = 0; i < level - 1; i++) cout << "| ";
        cout << "| " << endl;
        for (int i = 0; i < level - 1; i++) cout << "| ";
        cout << "+-(" << node->name << ")";
    }
    cout << endl;  // Ensuring consistent newlines after entries

    // Maintain correct order of printing
    vector<Node*> orderedChildren;
    for (const auto& child : node->children) 
	{
        orderedChildren.push_back(child.second.get());
    }

    // Ensure order of children is preserved (as per input)
    std::stable_sort(orderedChildren.begin(), orderedChildren.end(),
        [](Node* a, Node* b) { return a->name < b->name; });

    for (Node* child : orderedChildren) 
	{
        printNode(child, level + 1);
    }
}

// Function to print the filesystem tree
void printTree(istream& is) 
{
    shared_ptr<Node> root = readInput(is);
  	cout << endl; // fixed to add new line
    printNode(root.get());
}

// Recursive function to compute size of a directory
int computeSizeHelper(Node* node, const string& ext) {
    if (!node->isDirectory) {
        // If filtering by extension, only count files that match the extension
        if (ext.empty() || (node->name.size() >= ext.size() &&
                            node->name.substr(node->name.size() - ext.size()) == ext)) {
            return node->size;
        }
        return 0;  // Ignore files that don't match
    }

    int totalSize = 0;
    for (const auto& child : node->children) {
        totalSize += computeSizeHelper(child.second.get(), ext);
    }
    return totalSize;
}

// Function to compute the size of a directory
int computeSize(istream& is, string path) 
{
    shared_ptr<Node> root = readInput(is);
    Node* node = root.get();
    std::istringstream ss(path);
    string segment;
    while (getline(ss, segment, '/')) 
	{
        if (segment.empty()) continue;
        if (node->children.count(segment))
            node = node->children[segment].get();
        else
            return -1; // Path does not exist
    }
    return computeSizeHelper(node, "");
}

// Helper function to find the smallest directory meeting the condition
void findSmallest(Node* node, int targetSize, int& minSize, string& result, string path, const string& ext) {
    int size = computeSizeHelper(node, ext);

    // Ensure root / is not selected unless it's the only option
    if (node->isDirectory && size >= targetSize && size < minSize && path != "/") {
        minSize = size;
        result = path;
    }

    for (const auto& child : node->children) {
        findSmallest(child.second.get(), targetSize, minSize, result, path + child.second->name + "/", ext);
    }
}

// Function to find the smallest directory meeting the required space
string smallestDir(istream& is, int targetSize, string ext) 
{
    shared_ptr<Node> root = readInput(is);
    string result = "";  // Ensure it starts empty
    int minSize = INT_MAX;  // Ensure we find the smallest valid directory

    findSmallest(root.get(), targetSize, minSize, result, "/", ext);

    // If no valid directory is found, return "/"
    return result.empty() ? "/" : result;
}

// Helper function to list deleted files/directories
void listDeletedHelper(Node* node, vector<string>& toDelete, string path, const string& ext) 
{
    if (!node->isDirectory) {
        if (ext.empty() || (node->name.size() >= ext.size() &&
                            node->name.substr(node->name.size() - ext.size()) == ext)) 
							{
            toDelete.push_back(path);  // No extra '/'
        }
    } else {
        bool allChildrenDeleted = true;
        vector<string> subToDelete;

        for (const auto& child : node->children) 
		{
            listDeletedHelper(child.second.get(), subToDelete, path + child.second->name + "/", ext);
            if (!child.second->isDirectory || !child.second->children.empty()) 
			{
                allChildrenDeleted = false;
            }
        }

        // Ensure proper ordering of deletions
        toDelete.insert(toDelete.end(), subToDelete.begin(), subToDelete.end());

        // If all children are deleted, delete this directory too
        if (allChildrenDeleted) {
            toDelete.push_back(path);
        }
    }
}

// Function to list files/directories that would be deleted
void listDeleted(istream& is, int targetSize, string ext) 
{
    shared_ptr<Node> root = readInput(is);
    string smallestPath = smallestDir(is, targetSize, ext);

    if (smallestPath.empty() || smallestPath == "/") return;  // Ensure no invalid deletions

    Node* node = root.get();
    std::istringstream ss(smallestPath);
    string segment;
    
    while (getline(ss, segment, '/')) 
	{
        if (segment.empty()) continue;
        if (node->children.count(segment))
            node = node->children[segment].get();
        else
            return;  // Path doesn't exist, nothing to delete
    }

    vector<string> toDelete;
    listDeletedHelper(node, toDelete, smallestPath, ext);

    // Print deletions in expected order
    for (const auto& item : toDelete) 
	{
        cout << item << endl;
    }
}

