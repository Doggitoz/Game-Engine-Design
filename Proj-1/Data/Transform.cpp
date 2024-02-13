#include "Transform.h"

Transform::Transform() {
    this->position = new Vector3(0, 0, 0);
    this->scale = new Vector3(1, 1, 1);
}

void Transform::SetPosition(Vector3* p) {
    this->position = p;
}

void Transform::SetScale(Vector3* s) {
    this->scale = s;
}