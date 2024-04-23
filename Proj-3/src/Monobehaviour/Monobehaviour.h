#pragma once

#include "../Component/Transform.h"

class Node;

class Monobehaviour {
    public:
        Node* node;
        Transform transform;
        virtual void Start();
        virtual void Update();
};