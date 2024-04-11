#ifndef TIMER_H
#define TIMER_H

const int TARGET_FPS = 60;
const float TARGET_DELTATIME = 1.5f;  // second

class Timer
{
    public:
        void Tick();
        inline float GetDeltaTime() { return m_DeltaTime; } 
        inline static Timer* GetInstance() { return s_Instance = (s_Instance != nullptr)? s_Instance : new Timer(); }

    private:
        Timer() {};
        static Timer* s_Instance;
        float m_DeltaTime;
        float m_LastTime;

};

#endif  // TIMER_H
