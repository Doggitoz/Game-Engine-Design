#include <iostream>

using namespace std;

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