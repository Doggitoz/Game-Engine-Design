#include <iostream>
#include <algorithm>

#include "Node.h"

using namespace std;

Node::Node(std::string name) {
    this-> name = name;
}

Node::Node(std::string name, Node parent) {
    this->name = name;
    this->SetParent(parent);
}

Node* Node::operator*() {
    return this;
}

Node::Node() {
    Node("Node");
}

void Node::PrintAllChildren() {
    PrintAllChildren(0);
}

void Node::PrintAllChildren(int depth) {
    for (int i = 0; i < depth + 1; i++) {
        std::cout << "\t";
    }
    std::cout << this->name << std::endl;
    for (Node* i : children) {
        i->PrintAllChildren(depth + 1);
    }
}

Node* Node::GetParent() {
    return this->parent;
}

void Node::SetParent(Node node) {
    // Need to remove child from previous parent here somehow. This will cause huge issues later.
    this->parent = *node;
}

Node* Node::GetNodeInChildren(std::string name) {
    if (this->name == name)
        return this;
    if (this->children.size() == 0) return NULL;
    for (Node* n : children) {
        Node* check = n->GetNodeInChildren(name);
        if (check) return check;
    }
    return NULL;
}

void Node::AddChild(Node* node) {
    this->children.push_back(node);
}


void Node::PrintDetails() {
    cout << "Name: " << this->name << endl;
    cout << "Transform" << endl;
    cout << "\tPosition" << endl;
    cout << "\t\tx: " << this->transform.position->x << endl;
    cout << "\t\ty: " << this->transform.position->y << endl;
    cout << "\t\tz: " << this->transform.position->z << endl;
    cout << "\tScale" << endl;
    cout << "\t\tx: " << this->transform.scale->x << endl;
    cout << "\t\ty: " << this->transform.scale->y << endl;
    cout << "\t\tz: " << this->transform.scale->z << endl;

}