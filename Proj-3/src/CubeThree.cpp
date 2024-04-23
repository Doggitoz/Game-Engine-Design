#include <iostream>

using namespace std;

class CubeThree : public Monobehaviour {
    public:
        void Start();
        void Update();
};


void CubeThree::Start() {
    cout << "test!" << endl;
}

void CubeThree::Update() {
    cout << "updating!" << endl;
}