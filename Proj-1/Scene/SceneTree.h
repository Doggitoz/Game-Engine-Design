#pragma once

#include "../Core/Object.h"
#include "Node.h"

class SceneTree {
    public:
        std::vector<Node> nodes;
        void AddNode(Node obj);
        void ViewHierarchy();
        Node* GetNodeByName(std::string name);
};