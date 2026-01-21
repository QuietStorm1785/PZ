#include <string>
#include "com/google/common/util/concurrent/AbstractScheduledService.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {

protected AbstractScheduledService::AbstractScheduledService() {
    // TODO: Implement AbstractScheduledService
    return nullptr;
}

void AbstractScheduledService::startUp() {
    // TODO: Implement startUp
}

void AbstractScheduledService::shutDown() {
    // TODO: Implement shutDown
}

ScheduledExecutorService AbstractScheduledService::executor() {
    // TODO: Implement executor
    return nullptr;
}

std::string AbstractScheduledService::serviceName() {
    // TODO: Implement serviceName
    return "";
}

std::string AbstractScheduledService::toString() {
    // TODO: Implement toString
    return "";
}

bool AbstractScheduledService::isRunning() {
    // TODO: Implement isRunning
    return false;
}

State AbstractScheduledService::state() {
    // TODO: Implement state
    return nullptr;
}

void AbstractScheduledService::addListener(Listener listener, Executor executor) {
    // TODO: Implement addListener
}

std::exception AbstractScheduledService::failureCause() {
    // TODO: Implement failureCause
    return nullptr;
}

Service AbstractScheduledService::startAsync() {
    // TODO: Implement startAsync
    return nullptr;
}

Service AbstractScheduledService::stopAsync() {
    // TODO: Implement stopAsync
    return nullptr;
}

void AbstractScheduledService::awaitRunning() {
    // TODO: Implement awaitRunning
}

void AbstractScheduledService::awaitRunning(long timeout, TimeUnit unit) {
    // TODO: Implement awaitRunning
}

void AbstractScheduledService::awaitTerminated() {
    // TODO: Implement awaitTerminated
}

void AbstractScheduledService::awaitTerminated(long timeout, TimeUnit unit) {
    // TODO: Implement awaitTerminated
}

} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
