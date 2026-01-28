

// ...existing code up to the end of the zombie::GameTime class definition...

#pragma once
#include <string>
#include <unordered_map>
#include <fstream>

namespace zombie { namespace iso { namespace weather { class ClimateManager; } } }

namespace zombie {

class GameTime {
public:
    GameTime() = default;
    ~GameTime() = default;


    // Example members (expand as needed)
    double timeOfDay = 0.0; // 0.0 = midnight, 12.0 = noon
    int day = 1;
    int month = 1;
    int year = 1;
    double timeMultiplier = 1.0;

    // --- Helicopter fields ---
    static int HelicopterDay1;
    static int HelicopterTime1Start;
    static int HelicopterTime1End;

    // --- Mod data placeholder ---
    static std::unordered_map<std::string, std::string> modData;

    // --- Save/load ---
    void save(const std::string& filename);
    bool load(const std::string& filename);

    void update(double deltaHours) {
        timeOfDay += deltaHours * timeMultiplier;
        while (timeOfDay >= 24.0) {
            timeOfDay -= 24.0;
            ++day;
            int daysInMonth = getDaysInMonth(month, year);
            if (day > daysInMonth) {
                day = 1;
                ++month;
                if (month > 12) {
                    month = 1;
                    ++year;
                }
            }
        }
    }

    double getTimeOfDay() const { return timeOfDay; }
    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }
    void setTimeMultiplier(double mult) { timeMultiplier = mult; }
    double getTimeMultiplier() const { return timeMultiplier; }

    // --- AnimTimer nested class ---
    class AnimTimer {
    public:
        float Elapsed = 0.0f;
        float Duration = 0.0f;
        bool Finished = true;
        int Ticks = 0;
        GameTime* gameTime = nullptr;

        AnimTimer(GameTime* gt = nullptr) : gameTime(gt) {}

        void init(int ticks) {
            Ticks = ticks;
            Elapsed = 0.0f;
            Duration = ticks * (1.0f / 30.0f);
            Finished = false;
        }

        void update() {
            if (Finished || !gameTime) return;
            Elapsed += static_cast<float>(gameTime->getMultipliedSecondsSinceLastUpdate() * 60.0 / 30.0);
            if (Elapsed >= Duration) {
                Elapsed = Duration;
                Finished = true;
            }
        }

        float ratio() const {
            return Duration > 0.0f ? Elapsed / Duration : 1.0f;
        }

        bool finished() const {
            return Finished;
        }
    };

    // Stub for getMultipliedSecondsSinceLastUpdate (should be implemented as needed)
    double getMultipliedSecondsSinceLastUpdate() const { return 1.0 / 60.0; }

private:
    static bool isLeapYear(int y) {
        return (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0));
    }
    static int getDaysInMonth(int m, int y) {
        static const int days[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
        if (m == 2 && isLeapYear(y)) return 29;
        if (m >= 1 && m <= 12) return days[m-1];
        return 30;
    }
};

} // namespace zombie
#pragma once
#include <cstdint>

namespace zombie {

class GameTime {
public:
    GameTime() = default;
    ~GameTime() = default;

    // Example members (expand as needed)
    double timeOfDay = 0.0; // 0.0 = midnight, 12.0 = noon
    int day = 1;
    int month = 1;
    int year = 1;
    double timeMultiplier = 1.0;


    void update(double deltaHours) {
        timeOfDay += deltaHours * timeMultiplier;
        while (timeOfDay >= 24.0) {
            timeOfDay -= 24.0;
            ++day;
            int daysInMonth = getDaysInMonth(month, year);
            if (day > daysInMonth) {
                day = 1;
                ++month;
                if (month > 12) {
                    month = 1;
                    ++year;
                }
            }
        }
    }

private:
    static bool isLeapYear(int y) {
        return (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0));
    }
    static int getDaysInMonth(int m, int y) {
        static const int days[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
        if (m == 2 && isLeapYear(y)) return 29;
        if (m >= 1 && m <= 12) return days[m-1];
        return 30;
    }

    double getTimeOfDay() const { return timeOfDay; }
    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }
    void setTimeMultiplier(double mult) { timeMultiplier = mult; }
    double getTimeMultiplier() const { return timeMultiplier; }
};

} // namespace zombie
