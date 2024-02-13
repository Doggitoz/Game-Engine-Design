#include "Vector2.h"

Vector2::Vector2() {
    this->x = 0;
    this->y = 0;
}

Vector2::Vector2(float x, float y) {
    this->x = x;
    this->y = y;
}

Vector2 Vector2::operator+(Vector2 v) {
    return Vector2(this->x + v.x, this->y + v.y);
}

void Vector2::operator+=(Vector2 v) {
    this->x = this->x + v.x;
    this->y = this->y + v.y;
}