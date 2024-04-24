#pragma once

#include "Transform.cpp"
#include "Node.cpp"

class Monobehaviour {
    public:
        Monobehaviour(Node* n) { node = n; transform = n->transform; };
        Node* node;
        Transform transform;
        virtual void Start() {};
        virtual void Update() {};
};