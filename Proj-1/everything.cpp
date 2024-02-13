// Online C++ compiler to run C++ program online
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
using namespace std;

// Data types
class Vector2 {
    public:
        float x;
        float y;
        Vector2();
        Vector2(float x, float y);
        Vector2 operator+(Vector2 v);
        void operator+=(Vector2 v);
};

class Vector3 {
    public:
        float x;
        float y;
        float z;
        Vector3();
        Vector3(float x, float y, float z);
        Vector3 operator+(Vector3 v);
        void operator+=(Vector3 v);
        void AddVector(Vector3 v);
};

class Transform {
    public:
        Vector3* position;
        Vector3* scale;
        Transform();
        void SetPosition(Vector3* p);
        void SetScale(Vector3* s);
};

Transform::Transform() {
    this->position = new Vector3(0, 0, 0);
    this->scale = new Vector3(1, 1, 1);
}

void Transform::SetPosition(Vector3* p) {
    this->position = p;
}

void Transform::SetScale(Vector3* s) {
    this->scale = s;
}

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

void Vector3::operator+=(Vector3 v) {
    this->x = this->x + v.x;
    this->y = this->y + v.y;
    this->z = this->z + v.z;
}

void Vector3::AddVector(Vector3 v) {
    this->x = this->x + v.x;
    this->y = this->y + v.y;
    this->z = this->z + v.z;
}

//end Data Types

// Start Scene Types
class Object {
    
};

class Node : public Object {
    public:
        Transform transform;
        Node(std::string name);
        Node(std::string name, Node parent);
        Node();
        std::string name;
        std::vector<Node*> children;
        void SetParent(Node node);
        void PrintAllChildren();
        void PrintAllChildren(int depth);
        Node* GetParent();
        Node* GetNodeInChildren(std::string name);
        void AddChild(Node* node);
        Node* operator*();
        void PrintDetails();
    private:
        Node* parent;
};

class Node2D : public Node {
    public:
        Transform transform;
};

class SceneTree {
    public:
        std::list<Node*> nodes;
        void AddNode(Node* obj);
        void ViewHierarchy();
        Node* GetNodeByName(std::string name);
};

class Spatial : public Node {
    public:
        Spatial();
};

class Camera : public Spatial {
    public:
        Camera();
};

Spatial::Spatial() {
    Node("SpatialNode");
}

void Node::PrintDetails() {
    cout << "Name: " << this->name << endl;
    cout << "Transform" << endl;
    cout << "\tPosition" << endl;
    cout << "\t\tx: " << this->transform.position->x << endl;
    cout << "\t\ty: " << this->transform.position->y << endl;
    cout << "\t\tz: " << this->transform.position->z << endl;
    cout << "\tScale" << endl;
    cout << "\t\tx: " << this->transform.scale->x << endl;
    cout << "\t\ty: " << this->transform.scale->y << endl;
    cout << "\t\tz: " << this->transform.scale->z << endl;

}


Camera::Camera() {
    this->name = "MainCamera";
}

Node::Node(std::string name) {
    this-> name = name;
}

Node::Node(std::string name, Node parent) {
    this->name = name;
    this->SetParent(parent);
}

Node* Node::operator*() {
    return this;
}

Node::Node() {
    Node("Node");
}

void Node::PrintAllChildren() {
    PrintAllChildren(0);
}

void Node::PrintAllChildren(int depth) {
    for (int i = 0; i < depth + 1; i++) {
        std::cout << "\t";
    }
    std::cout << this->name << std::endl;
    for (Node* i : children) {
        i->PrintAllChildren(depth + 1);
    }
}

Node* Node::GetParent() {
    return this->parent;
}

void Node::SetParent(Node node) {
    // Need to remove child from previous parent here somehow. This will cause huge issues later.
    this->parent = *node;
}

Node* Node::GetNodeInChildren(std::string name) {
    if (this->name == name)
        return this;
    if (this->children.size() == 0) return NULL;
    for (Node* n : children) {
        Node* check = n->GetNodeInChildren(name);
        if (check) return check;
    }
    return NULL;
}

void Node::AddChild(Node* node) {
    this->children.push_back(node);
}

void SceneTree::AddNode(Node* obj) {
    nodes.push_back(obj);
}

void SceneTree::ViewHierarchy() {
    for (Node* i : nodes) {
        i->PrintAllChildren(0);
    }
}

Node* SceneTree::GetNodeByName(std::string name) {
    for (Node* i : nodes) {
        Node* search = i->GetNodeInChildren(name);
        if (search) return search;
    }
    return NULL;
}

// end Scene Types

// Start main
class MyGodotEngine {
    public:
        MyGodotEngine();
        SceneTree Scene;
        Camera MainCamera;
        SceneTree CreateScene();
        Node* CreateObjectInScene(std::string name);
        Camera CreateCamera();
};

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
    Scene.AddNode(*c);
    return c;
}

int main() {
    string in = "";
    MyGodotEngine godot = MyGodotEngine();
    Node* selected = NULL;
    while (in != "quit") {
        cout << "Enter command: ";
        cin >> in;
        cout << endl;
        if (in == "help") {
            cout << "Available commands: view_scene | add_node | add_camera | select_node | view_properties | modify_transform | clear_selected | quit" << endl;
        }
        else if (in == "view_scene") {
            cout << "-----------------------------" << endl;
            godot.Scene.ViewHierarchy();
            cout << "-----------------------------" << endl;
        }
        else if (in == "add_node") {
            string name = "";
            cout << "Adding node..." << endl;
            cout << "Name the node: ";
            cin >> name;
            cout << endl;
            if (name == "") name = "Node";
            if (!selected) godot.CreateObjectInScene(name);
            else {
                Node* n = new Node(name);
                n->SetParent(*selected);
                selected->AddChild(n);
            }
        }
        else if (in == "add_camera") {
            cout << "Adding camera..." << endl;
            godot.CreateCamera();
        }
        else if (in == "select_node") {
            string name = "";
            cout << "Selecing node..." << endl;
            cout << "What is the node name: ";
            cin >> name;
            cout << endl;
            selected = godot.Scene.GetNodeByName(name);
            if (!selected) cout << "Node not found." << endl;
            else cout << "Selected node " << name << "." << endl;
        }
        else if (in == "view_properties") {
            if (!selected) {
                cout << "No node selected." << endl;
                continue;
            }
            // print data here
            selected->PrintDetails();
        }
        else if (in == "modify_transform") {
            if (!selected) {
                cout << "No node selected." << endl;
                continue;
            }
            cout << "Moving up by one..." << endl;
            //selected.transform.position.AddVector(Vector3(0, 1, 0));
        }
        else if (in == "clear_selected") {
            selected = NULL;
        }
        else {
            cout << "Unknown command. Type help for commands." << endl;
        }
    }
    return 0;
}