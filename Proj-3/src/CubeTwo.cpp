#include <iostream>
#include "Time.cpp"

using namespace std;

class CubeTwo : public Monobehaviour {
    public:
        CubeTwo(Node* n) : Monobehaviour(n) {}
        void Start() override;
        void Update() override;
};


void CubeTwo::Start() {
    cout << "test!" << endl;
}

void CubeTwo::Update() {
    transform.scale = new Vector3(abs(cos(Time::time)), abs(sin(Time::time)), abs(tan(Time::time)));
}