#pragma once

class Vector2 {
    public:
        float x;
        float y;
        Vector2();
        Vector2(float x, float y);
        Vector2 operator+(Vector2 v);
        void operator+=(Vector2 v);
};