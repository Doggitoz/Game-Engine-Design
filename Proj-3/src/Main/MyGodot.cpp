#include <iostream>
#include <ctime>
#include <cmath>
#include <tchar.h>
#include <windows.h>
#include <chrono>
#include "../Core/SceneTree.h"
#include "../Core/Node.h"
#include "../Data/Vector3.h"
#include "../Monobehaviour/Monobehaviour.h"

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

#pragma region Time

class Time {
    public:
        Time();
        void Tick();
        static double time;
        static double deltaTime;
    private:
        chrono::high_resolution_clock::time_point startTime;
        chrono::high_resolution_clock::time_point prevTime;
};

double Time::time = 0;
double Time::deltaTime = 0;

Time::Time() {
    startTime = chrono::high_resolution_clock::now();
    prevTime = chrono::high_resolution_clock::now();
}

void Time::Tick() {
    auto now = chrono::high_resolution_clock::now();
    auto now_ms = chrono::time_point_cast<chrono::milliseconds>(now);
    auto total = now_ms - chrono::time_point_cast<chrono::milliseconds>(startTime);
    auto delta = now_ms - chrono::time_point_cast<chrono::milliseconds>(prevTime);
    prevTime = now;
    time = ((double) total.count()) / 1000;
    deltaTime = ((double) delta.count()) / 1000;
}

#pragma endregion

#pragma region Scripts
class CubeThree : public Monobehaviour {
    public:
        void Start();
        void Update();
};

class CubeTwo : public Monobehaviour {
    public:
        void Start();
        void Update();
};

void CubeTwo::Start() {
    cout << "test!" << endl;
}

void CubeTwo::Update() {
    cout << "updating!" << endl;
}

void CubeThree::Start() {
    cout << "test!" << endl;
}

void CubeThree::Update() {
    cout << "updating!" << endl;
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

    /*
    for each gameobject in each scene (probably jsut one scene)
        if has mesh, load in obj from current assets
    */

    // Start Direct3D
    System((string)"Direct3D.exe");

    double checkSum = 0;
    while (true) {
        _time.Tick();
        checkSum += _time.deltaTime;
        cout << "Time: " << _time._time.deltaTime << endl;
    }
    return 0;
}