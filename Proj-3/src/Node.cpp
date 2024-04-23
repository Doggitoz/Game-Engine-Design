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
        Node(string name, vector<string> mesh)
        Node(string name);
        Node();
        string name;
        vector<string> mesh;
        void Start();
        void Update();
        Node* operator*();
        void PrintDetails();
};

Node::Node() {
    Node("Node");
}

Node::Node(std::string name) {
    this-> name = name;
}

Node::Node(string name, vector<string> mesh) {
    this->name = name;
    this->mesh = mesh;
}

Node* Node::operator*() {
    return this;
}

void Node::PrintDetails() {
    cout << "Name: " << this->name << endl;
    cout << "Transform" << endl;
    cout << "\t" << transform;
}