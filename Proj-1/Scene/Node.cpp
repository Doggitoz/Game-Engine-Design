#include <iostream>
#include <algorithm>

#include "Node.h"

Node::Node(std::string name) {
    this-> name = name;
}

Node::Node(std::string name, Node* parent) {
    this->name = name;
    this->SetParent(parent);
}

void Node::PrintAllChildren() {
    int tabs = 0;
    Node* curr = this;
    while (curr->parent != NULL) {
        curr = curr->parent;
        tabs++;
    }
    for (Node* i : children) {
        for (int i = 0; i < tabs + 1; i++)
            std::cout << "\t";
        std::cout << i->name << std::endl;
        i->PrintAllChildren(tabs + 1);
    }
}

void Node::PrintAllChildren(int depth) {
    for (Node* i : children) {
        for (int i = 0; i < depth + 1; i++)
            std::cout << "\t";
        std::cout << i->name << std::endl;
        i->PrintAllChildren(depth + 1);
    }
}

Node* Node::GetParent() {
    return this->parent;
}

void Node::SetParent(Node* node) {
    // Need to remove child from previous parent here somehow. This will cause huge issues later.
    this->parent = node;
}

Node* Node::GetNodeInChildren(std::string name) {
    if (this->name == name)
        return this;
    if (this->children.size() == 0) return NULL;
    for (Node* n : children) {
        Node* check = GetNodeInChildren(name);
        if (check) return check;
    }
    return NULL;
}