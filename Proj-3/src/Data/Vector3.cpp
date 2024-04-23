#include "Vector3.h"

Vector3::Vector3() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Vector3::Vector3(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

std::ostream& operator<<(std::ostream& os, const Vector3& v) {
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

Vector3 Vector3::operator+(Vector3 v) {
    return Vector3(this->x + v.x, this->y + v.y, this->z + v.z);
}

void Vector3::operator+=(Vector3 v) {
    this->x = this->x + v.x;
    this->y = this->y + v.y;
    this->z = this->z + v.z;
}