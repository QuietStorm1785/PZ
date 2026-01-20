#include "com\google\common\util\concurrent/ServiceManager$ServiceManagerState.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {

void ServiceManager$ServiceManagerState::tryStartTiming(Service service) {
    // TODO: Implement tryStartTiming
}

void ServiceManager$ServiceManagerState::markReady() {
    // TODO: Implement markReady
}

void ServiceManager$ServiceManagerState::addListener(Listener listener, Executor executor) {
    // TODO: Implement addListener
}

void ServiceManager$ServiceManagerState::awaitHealthy() {
    // TODO: Implement awaitHealthy
}

void ServiceManager$ServiceManagerState::awaitHealthy(long timeout, TimeUnit unit) {
    // TODO: Implement awaitHealthy
}

void ServiceManager$ServiceManagerState::awaitStopped() {
    // TODO: Implement awaitStopped
}

void ServiceManager$ServiceManagerState::awaitStopped(long timeout, TimeUnit unit) {
    // TODO: Implement awaitStopped
}

void ServiceManager$ServiceManagerState::transitionService(Service service, State from, State to) {
    // TODO: Implement transitionService
}

void ServiceManager$ServiceManagerState::fireStoppedListeners() {
    // TODO: Implement fireStoppedListeners
}

void ServiceManager$ServiceManagerState::fireHealthyListeners() {
    // TODO: Implement fireHealthyListeners
}

void ServiceManager$ServiceManagerState::fireFailedListeners(Service service) {
    // TODO: Implement fireFailedListeners
}

new ServiceManager$ServiceManagerState::2("failed({service=" +) {
    // TODO: Implement 2
    return nullptr;
}

void ServiceManager$ServiceManagerState::executeListeners() {
    // TODO: Implement executeListeners
}

void ServiceManager$ServiceManagerState::checkHealthy() {
    // TODO: Implement checkHealthy
}

} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
