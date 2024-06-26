#include <iostream>
#include <ctime>
#include <cmath>
#include <tchar.h>
#include <windows.h>
#include <sstream>
#include <fstream>
#include <cstdio>
#include <filesystem>
#include <future>
#include "SceneTree.cpp"
#include "Node.cpp"
#include "Vector3.cpp"
#include "Monobehaviour.cpp"
#include "CubeTwo.cpp"
#include "CubeThree.cpp"
#include "Time.cpp"
#include "Mesh.cpp"

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

vector<string> sceneToObj(SceneTree scene) {
    vector<string> lines;

    lines.push_back("v," + SceneTree::mainCamera->position.toString());
    lines.push_back("u," + SceneTree::mainCamera->up.toString());
    lines.push_back("r," + SceneTree::mainCamera->right.toString());
    lines.push_back("f," + SceneTree::mainCamera->forward.toString());

    lines.push_back("l,1,1,1,0.7");
    lines.push_back("q,0,1.5,1.2,0.005");

    // Need to get camera details here.

    // Get each light here.
    for (Node* n : scene.nodes) {
        if (!n->hasMesh) continue;
        lines.push_back("________________");
        for (int i = 0; i < n->mesh.header.size(); i++) {
            char label = n->mesh.header.at(i);
            string header(1, label);
            Vector3 v = n->mesh.data.at(i);
            if (label == '_') {
                lines.push_back("________________");
                continue;
            }
            if (label == 'p') {
                v += *(n->transform.position);
            }
            // add other cases here if desired
            lines.push_back(header + "," + v.toString());
        }
    }

    return lines;
}

void WriteObjects(SceneTree scene) {
    string obj = "./objects.obj";

    vector<string> lines = sceneToObj(scene);

    // Open the output file in binary mode
    ofstream outfile(obj, std::ios::binary);
    if (!outfile) {
        return;
    }

    // Determine an appropriate buffer size for batching writes
    const size_t bufferSize = 1024 * 2;  // Adjust buffer size as needed

    // Buffer for accumulating string data
    string buffer;
    buffer.reserve(bufferSize);

    // Iterate over each string in the vector
    for (const string& str : lines) {
        // Append the current string and a newline character to the buffer
        buffer += str + '\n';

        // If buffer size reaches the threshold, write its contents to the file
        if (buffer.size() >= bufferSize) {
            outfile.write(buffer.data(), buffer.size());
            buffer.clear(); // Reset the buffer after writing
        }
    }

    // Write any remaining data in the buffer to the file
    if (!buffer.empty()) {
        outfile.write(buffer.data(), buffer.size());
        buffer.clear();
    }

    // Close the output file
    outfile.close();
}

#pragma endregion

static Time _time;
SceneTree currentScene;

int main() {
    cout << "Running..." << endl;

    _time = Time();

    // Initialize engine
    currentScene = SceneTree();

    // Read in all obj files on initialization
    Node* CubeOneNode = currentScene.AddNode(new Node("Cube1", ReadInPrefab("Cube1")));
    Node* CubeTwoNode = currentScene.AddNode(new Node("Cube2", ReadInPrefab("Cube2")));
    Monobehaviour* cubeTwoScript = new CubeTwo();
    CubeTwoNode->AddComponent(cubeTwoScript);
    Node* CubeThreeNode = currentScene.AddNode(new Node("Cube3", ReadInPrefab("Cube3")));
    Monobehaviour* cubeThreeScript = new CubeThree();
    CubeThreeNode->AddComponent(cubeThreeScript);

    // Start Direct3D
    cout << "Launching Direct3D..." << endl;
    System((string)"Direct3D.exe");

    // Clock variables
    float interval = 0.03333;
    float frameCounter = 0;
    float fixedCounter = 0;

    currentScene.Start();
    while (true) {
        _time.Tick();

        currentScene.Update();
        SceneTree::mainCamera->Update();
        fixedCounter += Time::deltaTime;
        frameCounter += Time::deltaTime;

        if (fixedCounter > Time::fixedInterval) {
            currentScene.FixedUpdate();
        }

        // Render
        if (frameCounter > interval) {
            WriteObjects(currentScene);
            frameCounter = 0;
        }
        
    }
    return 0;
}