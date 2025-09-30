/// Collen Larsen Z1930118
/// CSCI 340-3
/// April 4th 2025
// xml.cc

#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <map>
#include <queue>

#include "nodes.h"
#include "bintree.h"
#include "xml.h"

// Convert XML element to string
std::string to_string(const xml_element &element, bool opening) {
    std::string result;
    if (element.type == tag) {
        // Print <tag ...> if opening=true, or </tag> if opening=false
        result += (opening ? "<" : "</") + element.name;
        if (opening) {
            for (const auto &attr : element.attrs) {
                result += " " + attr.first + "=\"" + attr.second + "\"";
            }
            result += ">";
        } else {
            result += ">";
        }
    } else {
        // Just plain text
        result = element.fulltext;
    }
    return result;
}

// Find nodes by name
std::vector<XMLNODE*> xml_find_by_name(XMLNODE *root, const std::string &name) {
    std::vector<XMLNODE*> results;
    preorder(root, [&](XMLNODE* node) {
        if (node->data.name == name) {
            results.push_back(node);
        }
    });
    return results;
}

// Find nodes with a specific attribute
std::vector<XMLNODE*> xml_find_with_attr(XMLNODE *root, const std::string &attrname) {
    std::vector<XMLNODE*> results;
    preorder(root, [&](XMLNODE* node) {
        if (node->data.attrs.find(attrname) != node->data.attrs.end()) {
            results.push_back(node);
        }
    });
    return results;
}

// Add node to the tree
int xml_add_node(const xml_element &element, xml_tree_state &state, bool verbose) {
    XMLNODE *newNode = new XMLNODE(element);

    // If empty tree, new node is root.
    if (!state.root) {
        state.root = newNode;
        state.cur  = newNode;
    }
    // If somehow cur is null, error out.
    else if (!state.cur) {
        std::cerr << "Error: current node is null." << std::endl;
        delete newNode;
        return 1;
    }
    else {
        // If cur is plain text or closed => new sibling
        if (state.cur->data.type == plain || state.cur->data.closed) {
            state.cur->right    = newNode;
            newNode->parent     = state.cur->parent;
        }
        else {
            // else it's an open tag => new child
            state.cur->left   = newNode;
            newNode->parent   = state.cur;
        }
        // move cur to newly added node
        state.cur = newNode;
    }
    return 0;
}

// Close XML tag
int xml_close_tag(const std::string name, xml_tree_state &state, bool verbose) {
    XMLNODE *node = state.cur;
    // Climb upward until we find a node whose name matches.
    while (node && node->data.name != name) {
        node = tilted_find_parent(node);
    }
    if (node && node->data.name == name) {
        node->data.closed = true;
        // The assignment instructions say to set cur to the tag we just closed:
        state.cur = node;
        return 0;
    } else {
        std::cerr << "Error: unmatched closing tag for " << name << std::endl;
        return 1;
    }
}

// Handle plain text in XML
int xml_handle_plaintext(std::string &plaintext, xml_tree_state &state, bool verbose) {
    xml_element element(plain, "", plaintext, {});
    return xml_add_node(element, state, verbose);
}

// Parse XML tag
int xml_handle_tag(std::string &tagstring, xml_tree_state &state, bool verbose) {
    if (tagstring.size() < 3 || tagstring[0] != '<' || tagstring.back() != '>') {
        std::cerr << "Error: invalid tag format." << std::endl;
        return 1;
    }
    bool isClosing = (tagstring[1] == '/');
    // snip off < >
    std::string tagContent = tagstring.substr(isClosing ? 2 : 1,
                              tagstring.size() - (isClosing ? 3 : 2));
    if (isClosing) {
        // it’s a closing tag => do xml_close_tag
        return xml_close_tag(tagContent, state, verbose);
    }

    // else it's an opening tag. Possibly has attributes
    auto spacePos = tagContent.find(' ');
    std::string tagName = (spacePos == std::string::npos)
                            ? tagContent
                            : tagContent.substr(0, spacePos);

    std::string attrString = (spacePos == std::string::npos)
                            ? ""
                            : tagContent.substr(spacePos + 1);

    xml_element element(tag, tagName, tagstring, {});
    // parse attributes
    xml_handle_attributes(attrString, element.attrs, verbose);

    // add node
    return xml_add_node(element, state, verbose);
}

// Parse attributes of a tag
int xml_handle_attributes(const std::string &input,
                          std::map<std::string, std::string> &attrs,
                          bool verbose) {
    std::string::size_type pos = 0;
    int valid_attributes = 0;

    while (pos < input.size()) {
        // skip leading whitespace
        while (pos < input.size() && isspace(input[pos])) pos++;

        // find '='
        auto eqPos = input.find('=', pos);
        if (eqPos == std::string::npos) break; // no more pairs

        // extract key
        std::string key = input.substr(pos, eqPos - pos);
        pos = eqPos + 1;

        // must have quote
        if (pos >= input.size() || input[pos] != '"') {
            if (verbose) {
                std::cerr << "Error: attribute values must be quoted." << std::endl;
            }
            return valid_attributes;
        }
        // find closing quote
        auto quotePos = input.find('"', pos + 1);
        if (quotePos == std::string::npos) {
            if (verbose) {
                std::cerr << "ERROR: missing closing quote on attribute." << std::endl;
            }
            return valid_attributes;
        }

        // store the key->value pair
        std::string value = input.substr(pos + 1, quotePos - (pos + 1));
        attrs[key] = value;
        valid_attributes++;

        // jump past the closing quote
        pos = quotePos + 1;
    }

    // if leftover invalid text after attributes
    while (pos < input.size() && isspace(input[pos])) pos++;
    if (pos < input.size()) {
        if (verbose) {
            std::cerr << "ERROR: leftover invalid text in attributes: \""
                      << input.substr(pos) << "\"" << std::endl;
        }
        return 0; // indicates error
    }

    return valid_attributes;
}

// Print XML subtree
void xml_print_subtree(XMLNODE *root, std::ostream &ost) {
    preorder(root, [&](XMLNODE *node) {
        ost << to_string(node->data, true) << "\n";
    });
}

