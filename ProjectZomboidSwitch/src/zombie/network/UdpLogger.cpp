// UdpLogger.cpp
// Merged from Java source, including all inner classes as nested C++ classes.
#include "UdpLogger.h"

namespace zombie {
namespace network {

UdpLogger::UdpLogger() {}
UdpLogger::~UdpLogger() {}

void UdpLogger::log(const std::string& message) {
    logs.push_back(message);
}

const std::vector<std::string>& UdpLogger::getLogs() const {
    return logs;
}

// ...implement more nested class logic as needed...

} // namespace network
} // namespace zombie
