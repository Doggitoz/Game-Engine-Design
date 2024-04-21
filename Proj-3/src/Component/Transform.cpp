#include "Transform.h"

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

