#pragma once

#include "Node.cpp"
#include "Monobehaviour.cpp"
#include <vector>

class SceneTree {
    public:
        void Start();
        void Update();
        Node* AddNode(Node* obj);
        void AddScript(Monobehaviour* m);
        void ViewHierarchy();
        Node* GetNodeByName(std::string name);
        std::vector<Monobehaviour*> scripts;
        std::vector<Node*> nodes;
};


void SceneTree::Start() {
    for (Monobehaviour* m : scripts) {
        m->Start();
    }
}

void SceneTree::Update() {
    for (Monobehaviour* m : scripts) {
        m->Update();
    }
}

Node* SceneTree::AddNode(Node* obj) {
    nodes.push_back(obj);
    return obj;
}

void SceneTree::AddScript(Monobehaviour* m) {
    scripts.push_back(m);
}

Node* SceneTree::GetNodeByName(std::string name) {
    for (Node* i : nodes) {
        if (i->name == name) return i;
    }
    return NULL;
}