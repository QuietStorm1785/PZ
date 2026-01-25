// StatisticServer.cpp
// Merged from Java source, including all inner classes as nested C++ classes.
#include "StatisticServer.h"
#include <algorithm>

namespace zombie {
namespace network {

StatisticServer::StatisticServer() {}
StatisticServer::~StatisticServer() {}

void StatisticServer::logServerEvent(const std::string& eventName) {
    serverEvents.push_back(eventName);
}

int StatisticServer::getServerEventCount(const std::string& eventName) const {
    return std::count(serverEvents.begin(), serverEvents.end(), eventName);
}

// ...implement more nested class logic as needed...

} // namespace network
} // namespace zombie
