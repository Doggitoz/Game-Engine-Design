#pragma once

#include <iostream>
#include <string>

class Vector3 {
    public:
        float x;
        float y;
        float z;
        Vector3();
        Vector3(float x, float y, float z);
        Vector3 operator+(Vector3 v);
        void operator+=(Vector3 v);
};

std::ostream& operator<<(std::ostream& os, const Vector3& v);
