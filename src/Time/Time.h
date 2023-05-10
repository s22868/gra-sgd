
#ifndef GRASGD_TIME_H
#define GRASGD_TIME_H

const int TARGET_FPS = 60;
const float TARGET_DELTATIME = 1.5f;

class Time {
public:
    void Tick();
    inline float GetDeltaTime(){return deltaTime;}
    static Time *GetInstance() {
        return s_Instance = (s_Instance != nullptr) ? s_Instance : new Time();
    }

private:
    Time(){};
    float deltaTime;
    float lastTime;

    static Time *s_Instance;
};


#endif //GRASGD_TIME_H
