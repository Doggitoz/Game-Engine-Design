#include "SceneTree.h"

void SceneTree::AddNode(Node* obj) {
    nodes.push_back(obj);
}

void SceneTree::ViewHierarchy() {
    for (Node* i : nodes) {
        i->PrintAllChildren(0);
    }
}

Node* SceneTree::GetNodeByName(std::string name) {
    for (Node* i : nodes) {
        Node* search = i->GetNodeInChildren(name);
        if (search) return search;
    }
    return NULL;
}