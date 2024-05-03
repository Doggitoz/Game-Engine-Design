#pragma once

#include <iostream>
#include <string>
#include "Utils.cpp"

using namespace std;

class Vector3 {
    public:
        float x;
        float y;
        float z;
        Vector3();
        Vector3(float x, float y, float z);
        Vector3 operator+(Vector3 v);
        Vector3 operator-(Vector3 v);
        Vector3 operator*(float f);
        Vector3 operator*(double d);
        Vector3 operator/(float f);
        Vector3 operator/(double d);
        void operator*=(float f);
        void operator*=(double d);
        void operator+=(Vector3 v);
        void operator-=(Vector3 v);
        string toString();
        float magnitude();
};

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

Vector3 Vector3::operator+(Vector3 v) {
    return Vector3(this->x + v.x, this->y + v.y, this->z + v.z);
}

Vector3 Vector3::operator-(Vector3 v) {
    return Vector3(this->x - v.x, this->y - v.y, this->z - v.z);
}

Vector3 Vector3::operator*(float f) {
    return Vector3(this->x * f, this->y * f, this->z * f);
}

Vector3 Vector3::operator*(double d) {
    return Vector3(this->x * d, this->y * d, this->z * d);
}

Vector3 Vector3::operator/(double d) {
    return Vector3(this->x / d, this->y / d, this->z / d);
}

Vector3 Vector3::operator/(float f) {
    return Vector3(this->x / f, this->y / f, this->z / f);
}

void Vector3::operator*=(float f) {
    this->x * f;
    this->y * f;
    this->z * f;
}

void Vector3::operator*=(double d) {
    this->x * d;
    this->y * d;
    this->z * d;
}

void Vector3::operator+=(Vector3 v) {
    this->x = this->x + v.x;
    this->y = this->y + v.y;
    this->z = this->z + v.z;
}

void Vector3::operator-=(Vector3 v) {
    this->x = this->x - v.x;
    this->y = this->y - v.y;
    this->z = this->z - v.z;
}

string Vector3::toString() {
    return Utils::Truncate(x) + "," + Utils::Truncate(y) + "," + Utils::Truncate(z);
}

float Vector3::magnitude() {
    return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}