#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include "Transform.cpp"

using namespace std;


class Node {
    public:
        Transform transform;
        Node(std::string name);
        Node(std::string name, Node parent);
        Node();
        std::string name;
        void Start();
        void Update();
        Node* operator*();
        void PrintDetails();
};

Node::Node(std::string name) {
    this-> name = name;
}

Node* Node::operator*() {
    return this;
}

Node::Node() {
    Node("Node");
}

void Node::PrintDetails() {
    cout << "Name: " << this->name << endl;
    cout << "Transform" << endl;
    cout << "\t" << transform;
}