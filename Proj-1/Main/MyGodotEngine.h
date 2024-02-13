#pragma once

#include "../Scene/SceneTree.h"
#include "../Scene/Camera.h"
#include "../Scene/Node.h"

class MyGodotEngine {
    public:
        MyGodotEngine();
        SceneTree Scene;
        Camera MainCamera;
        SceneTree CreateScene();
        Node CreateObjectInScene(std::string name);
        Camera CreateCamera();
};