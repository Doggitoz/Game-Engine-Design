#pragma once

#include "../Core/SceneTree.h"
#include "../Component/Camera.h"
#include "../Core/Node.h"

class MyGodotEngine {
    public:
        MyGodotEngine();
        SceneTree Scene;
        Camera MainCamera;
        SceneTree CreateScene();
        Node* CreateObjectInScene(std::string name);
        Camera CreateCamera();
};