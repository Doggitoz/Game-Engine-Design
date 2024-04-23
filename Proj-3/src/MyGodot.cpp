#include <iostream>
#include <ctime>
#include <cmath>
#include <tchar.h>
#include <windows.h>
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


vector<string> ReadInPrefab(string prefabName) {
    vector<string> lines;
    string path = "./Prefabs/" + prefabName + ".prefab";
    ifstream myfile(path);
    if (myfile.is_open()) {
        string line;
        while (getline(myfile, line)) {
            cout << line << endl;
            lines.push_back(line);
        }
        myfile.close();
    } else {
        cout << "faiiled to open file: " << path << endl;
    }
    return lines;
}

void WriteObjects() {
    
}

static Time _time;
SceneTree currentScene;


int main() {
    cout << "Running..." << endl;

    _time = Time();

    // Initialize engine
    currentScene = SceneTree();

    // Read in all obj files on initialization
    vector<string> test = ReadInPrefab("Cube1");

    /*
    for each gameobject in each scene (probably jsut one scene)
        if has mesh, load in obj from current assets
    */

    // Start Direct3D
    System((string)"Direct3D.exe");

    double checkSum = 0;
    while (true) {
        _time.Tick();
    }
    return 0;
}