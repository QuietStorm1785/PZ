#pragma once
#include <chrono>
#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>

namespace zombie {
namespace util {

class PZCalendar {
private:
    std::chrono::system_clock::time_point timePoint;
    
public:
    PZCalendar() : timePoint(std::chrono::system_clock::now()) {}
    
    // Get current time in milliseconds since epoch
    static long long currentTimeMillis() {
        auto now = std::chrono::system_clock::now();
        auto duration = now.time_since_epoch();
        return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    }
    
    // Set time in milliseconds since epoch
    void setTimeInMillis(long long millis) {
        timePoint = std::chrono::system_clock::time_point(
            std::chrono::milliseconds(millis));
    }
    
    // Get time in milliseconds since epoch
    long long getTimeInMillis() const {
        auto duration = timePoint.time_since_epoch();
        return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    }
    
    // Convert to string representation
    std::string toString() const {
        auto time_t_val = std::chrono::system_clock::to_time_t(timePoint);
        std::tm tm = *std::localtime(&time_t_val);
        
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }
    
    // Get individual components
    int getYear() const {
        auto time_t_val = std::chrono::system_clock::to_time_t(timePoint);
        std::tm tm = *std::localtime(&time_t_val);
        return tm.tm_year + 1900;
    }
    
    int getMonth() const {
        auto time_t_val = std::chrono::system_clock::to_time_t(timePoint);
        std::tm tm = *std::localtime(&time_t_val);
        return tm.tm_mon + 1; // 1-12
    }
    
    int getDay() const {
        auto time_t_val = std::chrono::system_clock::to_time_t(timePoint);
        std::tm tm = *std::localtime(&time_t_val);
        return tm.tm_mday;
    }
    
    int getHour() const {
        auto time_t_val = std::chrono::system_clock::to_time_t(timePoint);
        std::tm tm = *std::localtime(&time_t_val);
        return tm.tm_hour;
    }
    
    int getMinute() const {
        auto time_t_val = std::chrono::system_clock::to_time_t(timePoint);
        std::tm tm = *std::localtime(&time_t_val);
        return tm.tm_min;
    }
    
    int getSecond() const {
        auto time_t_val = std::chrono::system_clock::to_time_t(timePoint);
        std::tm tm = *std::localtime(&time_t_val);
        return tm.tm_sec;
    }
};

} // namespace util
} // namespace zombie
