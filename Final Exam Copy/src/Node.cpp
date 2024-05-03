#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include "Transform.cpp"
#include "Monobehaviour.cpp"
#include "Mesh.cpp"

using namespace std;


class Node {
    public:
        Transform transform;
        Node(string name, vector<string> mesh);
        Node(string name);
        Node();
        string name;
        Mesh mesh;
        bool hasMesh;
        vector<Monobehaviour*> components;
        void Start();
        void Update();
        Node* operator*();
        void PrintDetails();
        void AddComponent(Monobehaviour* m);
};

Node::Node() {
    Node("Node");
}

Node::Node(string name) {
    this->name = name;
    this->hasMesh = false;
}

Node::Node(string name, vector<string> mesh) {
    this->name = name;
    this->mesh = Mesh(mesh);
    this->hasMesh = true;
}

Node* Node::operator*() {
    return this;
}

void Node::PrintDetails() {

}

void Node::AddComponent(Monobehaviour* m) {
    m->Setup(this, this->transform);
    components.push_back(m);
}