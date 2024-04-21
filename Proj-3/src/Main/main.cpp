#include <ctime>
#include <cmath>
#include <tchar.h>
#include <windows.h>

#include "MyGodotEngine.h"
#include "../Core/Node.h"
#include <iostream>

using namespace std;

#define ZERO(memory) ZeroMemory(&memory, sizeof(memory));

void System(string cmd) {
    STARTUPINFO startupInfo;
    PROCESS_INFORMATION processInfo;
    ZERO(startupInfo);
    ZERO(processInfo);
    CreateProcess(
        NULL, (LPSTR)cmd.c_str(), NULL, NULL, FALSE,
        0, NULL, NULL, &startupInfo, &processInfo
    );
}

int main() {
    cout << "hi" << endl;
    // Read in all obj files on initialization

    /*
    for each gameobject in each scene (probably jsut one scene)
        if has mesh, load in obj from current assets
    */

    // Start Direct3D
    System("Direct3D.exe");
    while (true) {

    }
    return 0;
}


// int terminal() {
//     string in = "";
//     MyGodotEngine godot = MyGodotEngine();
//     Node* selected = NULL;
//     while (in != "quit") {
//         cout << "Enter command: ";
//         cin >> in;
//         cout << endl;
//         if (in == "help") {
//             cout << "Available commands: view_scene | add_node | add_camera | select_node | view_properties | modify_transform | clear_selected | quit" << endl;
//         }
//         else if (in == "view_scene") {
//             cout << "-----------------------------" << endl;
//             godot.Scene.ViewHierarchy();
//             cout << "-----------------------------" << endl;
//         }
//         else if (in == "add_node") {
//             string name = "";
//             cout << "Adding node..." << endl;
//             cout << "Name the node: ";
//             cin >> name;
//             cout << endl;
//             if (name == "") name = "Node";
//             if (!selected) godot.CreateObjectInScene(name);
//             else {
//                 Node* n = new Node(name);
//                 n->SetParent(*selected);
//                 selected->AddChild(n);
//             }
//         }
//         else if (in == "add_camera") {
//             cout << "Adding camera..." << endl;
//             godot.CreateCamera();
//         }
//         else if (in == "select_node") {
//             string name = "";
//             cout << "Selecing node..." << endl;
//             cout << "What is the node name: ";
//             cin >> name;
//             cout << endl;
//             selected = godot.Scene.GetNodeByName(name);
//             if (!selected) cout << "Node not found." << endl;
//             else cout << "Selected node " << name << "." << endl;
//         }
//         else if (in == "view_properties") {
//             if (!selected) {
//                 cout << "No node selected." << endl;
//                 continue;
//             }
//             // print data here
//             selected->PrintDetails();
//         }
//         else if (in == "modify_transform") {
//             if (!selected) {
//                 cout << "No node selected." << endl;
//                 continue;
//             }
//             cout << "Moving up by one..." << endl;
//             //selected.transform.position.AddVector(Vector3(0, 1, 0));
//         }
//         else if (in == "clear_selected") {
//             selected = NULL;
//         }
//         else {
//             cout << "Unknown command. Type help for commands." << endl;
//         }
//     }
//     return 0;
// }