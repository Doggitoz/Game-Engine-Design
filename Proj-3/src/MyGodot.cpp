#include <iostream>
#include <ctime>
#include <cmath>
#include <tchar.h>
#include <windows.h>
#include <sstream>
#include <fstream>
#include "SceneTree.cpp"
#include "Node.cpp"
#include "Vector3.cpp"
#include "Monobehaviour.cpp"
#include "CubeTwo.cpp"
#include "CubeThree.cpp"
#include "Time.cpp"

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

#pragma region Obj reading/writing

vector<string> ReadInPrefab(string prefabName) {
    vector<string> lines;
    string path = "./Prefabs/" + prefabName + ".prefab";
    ifstream myfile(path);
    if (myfile.is_open()) {
        string line;
        while (getline(myfile, line)) {
            lines.push_back(line);
        }
        myfile.close();
    } else {
        cout << "faiiled to open file: " << path << endl;
    }
    return lines;
}

void WriteObjects(SceneTree scene) {
    string path = "./objects.obj";
    ofstream outputFile(path, ios::out | ios::trunc);
    if (outputFile.is_open()) {
        // Need to add important fields here
        outputFile << "v,0,0.99,2.4,1.5," << endl << "u,0,1,0," << endl << "r,1,0,0," << endl << "f,0,0,-1," << endl <<
            "l,1,1,1,0.7," << endl << "q,0,1.5,1.2,0.005," << endl << "________________" << endl;
        for (Node* n : scene.nodes) {
            for (string str : n->mesh) {
                // Need to split and apply transforms here.
                vector<string> tokens;
                istringstream iss(str);
                string token;
                while (getline(iss, token, ',')) {
                    tokens.push_back(token);
                }
                string out;
                if (tokens.size() == 0) {
                    out = str;
                } else if (tokens.at(0) == "p") {
                    out = "p,";
                    // Apply transformations
                    float newX = stof(tokens.at(1)) * n->transform.scale->x + n->transform.position->x;
                    out.append(to_string(newX) + ",");
                    float newY = stof(tokens.at(2)) * n->transform.scale->y + n->transform.position->y;
                    out.append(to_string(newY)+ ",");
                    float newZ = stof(tokens.at(3)) * n->transform.scale->z + n->transform.position->z;
                    out.append(to_string(newZ)+ ",");
                } else {
                    out = str;
                }
                outputFile << out << endl;
            }
            outputFile << "________________" << endl;
        }
    } else {
        cout << "unable to open objects file" << endl;
    }
}

#pragma endregion

static Time _time;
SceneTree currentScene;

float TimeLi() {
    return (float)clock()/CLOCKS_PER_SEC;
}

int main() {
    cout << "Running..." << endl;

    _time = Time();

    // Initialize engine
    currentScene = SceneTree();

    // Read in all obj files on initialization
    Node* CubeOneNode = currentScene.AddNode(new Node("Cube1", ReadInPrefab("Cube1")));
    Node* CubeTwoNode = currentScene.AddNode(new Node("Cube2", ReadInPrefab("Cube2")));
    currentScene.AddScript(new CubeTwo(CubeTwoNode));
    Node* CubeThreeNode = currentScene.AddNode(new Node("Cube3", ReadInPrefab("Cube3")));
    currentScene.AddScript(new CubeThree(CubeThreeNode));

    // Start Direct3D
    System((string)"Direct3D.exe");

    currentScene.Start();
    float interval = 0.1;
    float localTime = TimeLi();
    while (true) {
        _time.Tick();
        if (localTime<TimeLi()) {
            currentScene.Update();
            WriteObjects(currentScene);
            localTime += interval;
        }
    }
    return 0;
}