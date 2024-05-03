#pragma once

#include "Monobehaviour.cpp"
#include "Time.cpp"

class Rigidbody : public Monobehaviour {
    public:
        Rigidbody(float mass, float gravity);
        float gravity;
        float mass;
        Vector3 velocity = Vector3();
        Vector3 acceleration = Vector3();
        void FixedUpdate() override;
};

void Rigidbody::FixedUpdate() {
    this->velocity += this->acceleration * Time::fixedInterval;
    *this->transform.position -= this->velocity * Time::fixedInterval;
}

Rigidbody::Rigidbody(float mass, float gravity) {
    if (gravity > 0) gravity *= -1;
    this->gravity = gravity;
    this->mass = mass;
}