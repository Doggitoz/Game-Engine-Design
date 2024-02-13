#pragma once

#include <vector>
#include <string>
#include "../Core/Object.h"

class Node : public Object {
    public:
        Node(std::string name);
        Node(std::string name, Node* parent);
        std::string name;
        std::vector<Node*> children;
        void SetParent(Node* node);
        void PrintAllChildren();
        void PrintAllChildren(int depth);
        Node* GetParent();
        Node* GetNodeInChildren(std::string name);
    private:
        Node* parent;
};