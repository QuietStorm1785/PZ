// StatisticClient.cpp
// Merged from Java source, including all inner classes as nested C++ classes.
#include "StatisticClient.h"
#include <algorithm>

namespace zombie {
namespace network {

StatisticClient::StatisticClient() {}
StatisticClient::~StatisticClient() {}

void StatisticClient::recordEvent(const std::string& eventName) {
    events.push_back(eventName);
}

int StatisticClient::getEventCount(const std::string& eventName) const {
    return std::count(events.begin(), events.end(), eventName);
}

// ...implement more nested class logic as needed...

} // namespace network
} // namespace zombie
