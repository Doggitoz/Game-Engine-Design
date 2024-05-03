#pragma once

#include <iostream>
#include <string>
#include "Utils.cpp"

using namespace std;

class Matrix4 {
    public:
        float x;
        float y;
        float z;
        float w;
        Matrix4();
        Matrix4(float x, float y, float z, float w);
        Matrix4 operator+(Matrix4 m);
        void operator+=(Matrix4 m);
        void operator+=(Vector3 v);
        void operator-=(Matrix4 m);
        void operator-=(Vector3 v);
        string toString();
};
std::ostream& operator<<(std::ostream& os, const Matrix4& m);


Matrix4::Matrix4() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->w = 0;
}

Matrix4::Matrix4(float x, float y, float z, float w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

std::ostream& operator<<(std::ostream& os, const Matrix4& m) {
    os << "(" << m.x << ", " << m.y << ", " << m.z << ", " << m.w << ")";
    return os;
}

Matrix4 Matrix4::operator+(Matrix4 m) {
    return Matrix4(this->x + m.x, this->y + m.y, this->z + m.z, this->w + m.w);
}

void Matrix4::operator+=(Matrix4 m) {
    this->x = this->x + m.x;
    this->y = this->y + m.y;
    this->z = this->z + m.z;
    this->w = this->w + m.w;
}

void Matrix4::operator+=(Vector3 v) {
    this->x = this->x + v.x;
    this->y = this->y + v.y;
    this->z = this->z + v.z;
}

void Matrix4::operator-=(Matrix4 m) {
    this->x = this->x - m.x;
    this->y = this->y - m.y;
    this->z = this->z - m.z;
    this->w = this->w - m.w;
}

void Matrix4::operator-=(Vector3 v) {
    this->x = this->x - v.x;
    this->y = this->y - v.y;
    this->z = this->z - v.z;
}

string Matrix4::toString() {
    return Utils::Truncate(x) + "," + Utils::Truncate(y) + "," + Utils::Truncate(z) + "," + Utils::Truncate(w);
}