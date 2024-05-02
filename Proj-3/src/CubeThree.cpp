#include <iostream>
#include "Time.cpp"

using namespace std;

class CubeThree : public Monobehaviour {
    public:
        CubeThree() : Monobehaviour() {}
        void Start() override;
        void Update() override;
};


void CubeThree::Start() {
    //cout << "test!" << endl;
}

void CubeThree::Update() {
    transform.position->y = sin(Time::time);
}