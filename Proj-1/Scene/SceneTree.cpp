#include "SceneTree.h"

void SceneTree::AddNode(Node node) {
    nodes.push_back(node);
}

void SceneTree::ViewHierarchy() {
    for (Node i : nodes) {
        i.PrintAllChildren(0);
    }
}

Node* SceneTree::GetNodeByName(std::string name) {
    for (Node i : nodes) {
        Node* search = i.GetNodeInChildren(name);
        if (search) return search;
    }
    return NULL;
}