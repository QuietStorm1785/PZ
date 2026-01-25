
// NAMESPACE WRAP BEGIN
namespace zombie {
namespace network {

#include "ConnectionManager.h"


#include <iostream>
#include <chrono>
#include <iomanip>
#include <ctime>

std::string ConnectionManager::s_logSdfFormat = "%d-%m-%y %H:%M:%S";

ConnectionManager::ConnectionManager() {
    // No special constructor logic needed
}

ConnectionManager::~ConnectionManager() {
    // No special destructor logic needed
}

void ConnectionManager::log(const std::string& tag, const std::string& message, void* udpConnection) {
    // Ported from Java: log method
    // Print timestamp, tag, message, and connection pointer (if any)
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm tm_buf;
#if defined(_WIN32)
    localtime_s(&tm_buf, &now_c);
#else
    localtime_r(&now_c, &tm_buf);
#endif
    char timeStr[32];
    std::strftime(timeStr, sizeof(timeStr), "%d-%m-%y %H:%M:%S", &tm_buf);
    std::cout << "[" << timeStr << "] > ConnectionManager: [" << tag << "] \"" << message << "\" connection: " << udpConnection << std::endl;
}

} // namespace network
} // namespace zombie
// NAMESPACE WRAP END
