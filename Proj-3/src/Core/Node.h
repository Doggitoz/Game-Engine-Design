#pragma once

#include <vector>
#include <string>
#include "../Component/Transform.h"

class Node {
    public:
        Transform transform;
        Node(std::string name);
        Node(std::string name, Node parent);
        Node();
        std::string name;
        std::vector<Node*> children;
        void SetParent(Node node);
        void PrintAllChildren();
        void PrintAllChildren(int depth);
        Node* GetParent();
        Node* GetNodeInChildren(std::string name);
        void AddChild(Node* node);
        Node* operator*();
        void PrintDetails();
    private:
        Node* parent;
};