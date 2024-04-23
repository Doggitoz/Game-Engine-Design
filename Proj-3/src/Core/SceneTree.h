#pragma once

#include "Node.h"
#include <list>

class SceneTree {
    public:
        std::list<Node*> nodes;
        void Start();
        void Update();
        void AddNode(Node* obj);
        void ViewHierarchy();
        Node* GetNodeByName(std::string name);
};