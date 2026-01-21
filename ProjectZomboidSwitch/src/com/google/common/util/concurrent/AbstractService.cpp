#include <string>
#include "com/google/common/util/concurrent/AbstractService.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {

protected AbstractService::AbstractService() {
    // TODO: Implement AbstractService
    return nullptr;
}

Service AbstractService::startAsync() {
    // TODO: Implement startAsync
    return nullptr;
}

Service AbstractService::stopAsync() {
    // TODO: Implement stopAsync
    return nullptr;
}

void AbstractService::awaitRunning() {
    // TODO: Implement awaitRunning
}

void AbstractService::awaitRunning(long timeout, TimeUnit unit) {
    // TODO: Implement awaitRunning
}

void AbstractService::awaitTerminated() {
    // TODO: Implement awaitTerminated
}

void AbstractService::awaitTerminated(long timeout, TimeUnit unit) {
    // TODO: Implement awaitTerminated
}

void AbstractService::checkCurrentState(State expected) {
    // TODO: Implement checkCurrentState
}

void AbstractService::notifyStarted() {
    // TODO: Implement notifyStarted
}

void AbstractService::notifyStopped() {
    // TODO: Implement notifyStopped
}

void AbstractService::notifyFailed(std::exception cause) {
    // TODO: Implement notifyFailed
}

bool AbstractService::isRunning() {
    // TODO: Implement isRunning
    return false;
}

State AbstractService::state() {
    // TODO: Implement state
    return nullptr;
}

std::exception AbstractService::failureCause() {
    // TODO: Implement failureCause
    return nullptr;
}

void AbstractService::addListener(Listener listener, Executor executor) {
    // TODO: Implement addListener
}

std::string AbstractService::toString() {
    // TODO: Implement toString
    return "";
}

void AbstractService::executeListeners() {
    // TODO: Implement executeListeners
}

void AbstractService::starting() {
    // TODO: Implement starting
}

void AbstractService::running() {
    // TODO: Implement running
}

void AbstractService::stopping(State from) {
    // TODO: Implement stopping
}

void AbstractService::terminated(State from) {
    // TODO: Implement terminated
}

void AbstractService::failed(State from, std::exception cause) {
    // TODO: Implement failed
}

new AbstractService::5("failed({from =, cause =) {
    // TODO: Implement 5
    return nullptr;
}

} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
