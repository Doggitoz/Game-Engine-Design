#pragma once

#include "Vector3.cpp"
#include <iostream>
#include <string>

class Transform {
    public:
        Vector3* position;
        Vector3* scale;
        Vector3* rotation;
        Transform();
        Transform(Vector3* p, Vector3* s, Vector3* r);
};

std::ostream& operator<<(std::ostream& os, const Transform& t);

Transform::Transform() {
    this->position = new Vector3(0, 0, 0);
    this->scale = new Vector3(1, 1, 1);
    this->rotation = new Vector3(0, 0, 0);
}

Transform::Transform(Vector3* p, Vector3* s, Vector3* r) {
    this->position = p;
    this->scale = s;
    this->rotation = r;
}

std::ostream& operator<<(std::ostream& os, const Transform& t) {
    std::cout << "Position: " << t.position << std::endl;
    std::cout << "Scale: " << t.scale << std::endl;
    std::cout << "Rotation: " << t.rotation << std::endl;
    return os;
}