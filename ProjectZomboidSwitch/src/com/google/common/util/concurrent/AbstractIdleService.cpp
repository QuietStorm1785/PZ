#include <string>
#include "com\google\common\util\concurrent/AbstractIdleService.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {

protected AbstractIdleService::AbstractIdleService() {
    // TODO: Implement AbstractIdleService
    return nullptr;
}

Executor AbstractIdleService::executor() {
    // TODO: Implement executor
    return nullptr;
}

std::string AbstractIdleService::toString() {
    // TODO: Implement toString
    return "";
}

bool AbstractIdleService::isRunning() {
    // TODO: Implement isRunning
    return false;
}

State AbstractIdleService::state() {
    // TODO: Implement state
    return nullptr;
}

void AbstractIdleService::addListener(Listener listener, Executor executor) {
    // TODO: Implement addListener
}

std::exception AbstractIdleService::failureCause() {
    // TODO: Implement failureCause
    return nullptr;
}

Service AbstractIdleService::startAsync() {
    // TODO: Implement startAsync
    return nullptr;
}

Service AbstractIdleService::stopAsync() {
    // TODO: Implement stopAsync
    return nullptr;
}

void AbstractIdleService::awaitRunning() {
    // TODO: Implement awaitRunning
}

void AbstractIdleService::awaitRunning(long timeout, TimeUnit unit) {
    // TODO: Implement awaitRunning
}

void AbstractIdleService::awaitTerminated() {
    // TODO: Implement awaitTerminated
}

void AbstractIdleService::awaitTerminated(long timeout, TimeUnit unit) {
    // TODO: Implement awaitTerminated
}

std::string AbstractIdleService::serviceName() {
    // TODO: Implement serviceName
    return "";
}

} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
