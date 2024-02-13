#pragma once

#include "Node.h"
#include "../Data/Transform.h"
#include "../Data/Vector3.h"

class Spatial : public Node {
    public:
        Transform* transform;
        Spatial();
};