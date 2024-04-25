#pragma once

#include "Monobehaviour.cpp"

class Rigidbody : public Monobehaviour {
    public:
        Rigidbody(float mass, float gravity = 9.8);
        float gravity;
        float mass;
}

Rigidbody::Rigidbody(float mass, float gravity = 9.8) {
    this->gravity = gravity;
    this->mass = mass;
}