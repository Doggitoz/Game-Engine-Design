#include "MyGodotEngine.h"

MyGodotEngine::MyGodotEngine() {
    CreateScene();
}

SceneTree MyGodotEngine::CreateScene(){
    Scene = SceneTree();
    return Scene;
}

Node* MyGodotEngine::CreateObjectInScene(std::string name) {
    Node* n = new Node(name);
    Scene.AddNode(n);
    return n;
}

Camera MyGodotEngine::CreateCamera() {
    Camera c = Camera();
    MainCamera = c;
    //Scene.AddNode(*c);
    return c;
}