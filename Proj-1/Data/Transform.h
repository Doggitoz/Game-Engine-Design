#pragma once

#include "Vector3.h"

class Transform {
    public:
        Vector3* position;
        Vector3* scale;
        Transform();
        void SetPosition(Vector3* p);
        void SetScale(Vector3* s);
};