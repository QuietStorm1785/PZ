#include <string>
#include "com/google/common/util/concurrent/AbstractExecutionThreadService.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {

protected AbstractExecutionThreadService::AbstractExecutionThreadService() {
    // TODO: Implement AbstractExecutionThreadService
    return nullptr;
}

void AbstractExecutionThreadService::startUp() {
    // TODO: Implement startUp
}

void AbstractExecutionThreadService::shutDown() {
    // TODO: Implement shutDown
}

void AbstractExecutionThreadService::triggerShutdown() {
    // TODO: Implement triggerShutdown
}

Executor AbstractExecutionThreadService::executor() {
    // TODO: Implement executor
    return nullptr;
}

std::string AbstractExecutionThreadService::toString() {
    // TODO: Implement toString
    return "";
}

bool AbstractExecutionThreadService::isRunning() {
    // TODO: Implement isRunning
    return false;
}

State AbstractExecutionThreadService::state() {
    // TODO: Implement state
    return nullptr;
}

void AbstractExecutionThreadService::addListener(Listener listener, Executor executor) {
    // TODO: Implement addListener
}

std::exception AbstractExecutionThreadService::failureCause() {
    // TODO: Implement failureCause
    return nullptr;
}

Service AbstractExecutionThreadService::startAsync() {
    // TODO: Implement startAsync
    return nullptr;
}

Service AbstractExecutionThreadService::stopAsync() {
    // TODO: Implement stopAsync
    return nullptr;
}

void AbstractExecutionThreadService::awaitRunning() {
    // TODO: Implement awaitRunning
}

void AbstractExecutionThreadService::awaitRunning(long timeout, TimeUnit unit) {
    // TODO: Implement awaitRunning
}

void AbstractExecutionThreadService::awaitTerminated() {
    // TODO: Implement awaitTerminated
}

void AbstractExecutionThreadService::awaitTerminated(long timeout, TimeUnit unit) {
    // TODO: Implement awaitTerminated
}

std::string AbstractExecutionThreadService::serviceName() {
    // TODO: Implement serviceName
    return "";
}

} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
