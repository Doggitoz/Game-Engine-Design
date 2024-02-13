#include "MyGodotEngine.h"
#include "../Scene/Node.h"
#include <iostream>

using namespace std;

int main() {
    string in = "";
    MyGodotEngine godot = MyGodotEngine();
    Node* selected = NULL;
    while (in != "quit") {
        cout << "Enter command: ";
        cin >> in;
        cout << endl;
        if (in == "help") {
            cout << "Available commands: view_scene | add_node | add_camera | select_node | view_properties | modify_transform | quit" << endl;
        }
        else if (in == "view_scene") {
            godot.Scene.ViewHierarchy();
        }
        else if (in == "add_node") {
            string name = "";
            cout << "Adding node..." << endl;
            cout << "Name the node: ";
            cin >> name;
            cout << endl;
            if (name == "") name = "Node";
            godot.CreateObjectInScene(name);
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
        else if (in == "view_properies") {
            if (!selected) {
                cout << "No node selected." << endl;
                break;
            }
            // print data here
            cout << "output data here" << endl;
        }
        else if (in == "modify_transform") {
            if (!selected) {
                cout << "No node selected." << endl;
                break;
            }
        }
        else {
            cout << "Unknown command. Type help for commands." << endl;
        }
    }
    return 0;
}