#pragma once

#include "Transform.cpp"
#include "Node.cpp"

class Node;

class Monobehaviour {
    public:
        Node* node;
        Transform transform;
        bool isActive = true;
        void Setup(Node* n, Transform t) { this->node = n; this->transform = t; };
        virtual void Start() {};
        virtual void Update() {};
        virtual void FixedUpdate() {};
};