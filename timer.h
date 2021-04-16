#include <chrono>  // Timer class

class Timer {
    private:
        using hrClock = std::chrono::high_resolution_clock;
        using duration = std::chrono::duration<double>;
        std::chrono::time_point<hrClock> start;
    public:
        void set() {
            start= hrClock::now();
        }
        double elapsed() const{
            return duration(hrClock::now() -start).count();
        }
};
