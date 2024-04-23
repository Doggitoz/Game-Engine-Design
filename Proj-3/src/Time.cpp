#include <chrono>

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