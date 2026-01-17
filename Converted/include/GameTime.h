#pragma once

namespace zombie {

/**
 * Manages game time, day/night cycle, and time-based events
 * Converted from zombie.GameTime
 */
class GameTime {
public:
    static GameTime* getInstance();
    
    GameTime();
    
    // Update the game time based on elapsed time
    void update(bool sleeping);
    
    // Time management
    float getTimeOfDay() const { return timeOfDay; }
    void setTimeOfDay(float time) { timeOfDay = time; }
    
    int getDay() const { return day; }
    void setDay(int d) { day = d; }
    
    int getMonth() const { return month; }
    void setMonth(int m) { month = m; }
    
    // FPS management
    float getFPSMultiplier() const { return fpsMultiplier; }
    void setFPSMultiplier(float mult) { fpsMultiplier = mult; }
    
    float getMultiplier() const { return multiplier; }
    void setMultiplier(float mult) { multiplier = mult; }
    
    // Day/night cycle
    float getNightTint() const { return nightTint; }
    float getAmbient() const { return ambient; }
    
    // Delta time (seconds since last update)
    float getDeltaTime() const { return deltaTime; }
    
private:
    static GameTime* instance;
    
    float timeOfDay;        // 0.0 - 24.0 (hour of day)
    int day;                // Days since start
    int month;              // Month (1-12)
    
    float nightTint;        // 0.0 (night) to 1.0 (day)
    float ambient;          // Ambient light level
    float ambientMax;
    float ambientMin;
    
    float fpsMultiplier;    // Correction for actual FPS vs target
    float multiplier;       // Game speed multiplier
    
    float deltaTime;        // Time since last update (seconds)
    float lastUpdate;       // Last update time
};

} // namespace zombie
