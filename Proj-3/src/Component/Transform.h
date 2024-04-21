#pragma once

#include "../Data/Vector3.h"

class Transform {
    public:
        Vector3* position;
        Vector3* scale;
        Vector3* rotation;
        Transform();
        Transform(Vector3* p, Vector3* s, Vector3* r);
};