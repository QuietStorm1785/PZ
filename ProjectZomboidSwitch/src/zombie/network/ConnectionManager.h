
#pragma once

// NAMESPACE WRAP BEGIN
namespace zombie {
namespace network {

// Ported from Java: ConnectionManager

class ConnectionManager {
public:
    ConnectionManager();
    ~ConnectionManager();

    // Ported static log method from Java
    static void log(const std::string& tag, const std::string& message, void* udpConnection = nullptr);

private:
    // Ported static field from Java
    static std::string s_logSdfFormat;
};

} // namespace network
} // namespace zombie
// NAMESPACE WRAP END
