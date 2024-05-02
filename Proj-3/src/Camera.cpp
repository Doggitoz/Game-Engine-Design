#pragma once

#include <string>
#include <vector>
#include <Windows.h>
#include "Vector3.cpp"
#include "Utils.cpp"
#include "Matrix4.cpp"
#include "Time.cpp"

using namespace std;

class Camera {
    public:
        Camera();
        Camera(Matrix4 p, Vector3 u, Vector3 r, Vector3 f);
        Vector3 up;
        Vector3 right;
        Vector3 forward;
        Matrix4 position;
        void LookAt(Vector3 v);
        void Update();
};

Camera::Camera() {
    this->position = Matrix4(0, 1, 2.5, 1.5);
    this->up = Vector3(0, 1, 0);
    this->right = Vector3(1, 0, 0);
    this->forward = Vector3(0, 0, -1);
}

Camera::Camera(Matrix4 p, Vector3 u, Vector3 r, Vector3 f) {
    this->position = p;
    this->up = u;
    this->right = r;
    this->forward = f;
}

void Camera::LookAt(Vector3 v) {

}

void Camera::Update() {
    if (GetAsyncKeyState(0x57)) { // W
        this->position += this->forward * Time::deltaTime;
    }
    else if (GetAsyncKeyState(0x53)) { // S
        this->position -= this->forward * Time::deltaTime;
    }

    if (GetAsyncKeyState(0x44)) { // D
        this->position += this->right * Time::deltaTime;
    }
    else if (GetAsyncKeyState(0x41)) { // A
        this->position -= this->right * Time::deltaTime;
    }

    if (GetAsyncKeyState(0x45)) { // E
        this->position += this->up * Time::deltaTime;
    }
    else if (GetAsyncKeyState(0x51)) { // Q
        this->position -= this->up * Time::deltaTime;
    }
}