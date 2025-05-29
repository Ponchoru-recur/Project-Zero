#pragma once

#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <unordered_map>

class timer {
   public:
    static int create(float milliseconds_) {
        int id = nextID++;
        if (id >= timers.size()) {
            timers.resize(id + 1);
            milliseconds.resize(id + 1);
        }
        timers[id] = std::chrono::steady_clock::now();
        milliseconds[id] = milliseconds_;
        return id;
    }

    static bool wait_till(int id) {
        if (id < 0 || id >= (int)timers.size()) {
            std::cout << "Something went wrong with the timer array, check me out!\n";
            return false;
        }
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - timers[id]);
        if (elapsed.count() >= milliseconds[id]) {
            timers[id] = std::chrono::steady_clock::now();
            return true;
        }

        return false;
    }

    // Get ID by inserting variable that has create();
    static int getTimerID(int ID) {
        return ID;
    }

    // Modifies the time
    static void modtimer(int ID, float milliseconds_) {
        milliseconds[ID] = milliseconds_;
    }

   private:
    // static inline std::unordered_map<int, std::chrono::time_point<std::chrono::steady_clock>> timers;
    static inline std::vector<std::chrono::time_point<std::chrono::steady_clock>> timers;
    static inline std::vector<float> milliseconds;
    static inline int nextID = 0;
};
