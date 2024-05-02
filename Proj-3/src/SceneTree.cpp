#pragma once

#include "Node.cpp"
#include "Monobehaviour.cpp"
#include "Camera.cpp"
#include <vector>

class SceneTree {
    public:
        void Start();
        void Update();
        void FixedUpdate();
        Node* AddNode(Node* obj);
        void ViewHierarchy();
        Node* GetNodeByName(std::string name);
        std::vector<Node*> nodes;
        static Camera* mainCamera;
};

Camera* SceneTree::mainCamera = new Camera();

void SceneTree::Start() {
    for (Node* n : nodes) {
        for (Monobehaviour* m : n->components)
            m->Start();
    }
}

void SceneTree::Update() {
    for (Node* n : nodes) {
        for (Monobehaviour* m : n->components)
            m->Update();
    }
}

void SceneTree::FixedUpdate() {
    for (Node* n : nodes) {
        for (Monobehaviour* m : n->components)
            m->FixedUpdate();
    }
}

Node* SceneTree::AddNode(Node* obj) {
    nodes.push_back(obj);
    return obj;
}

Node* SceneTree::GetNodeByName(std::string name) {
    for (Node* i : nodes) {
        if (i->name == name) return i;
    }
    return NULL;
}