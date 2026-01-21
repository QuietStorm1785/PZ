#include <string>
#include "com/google/common/eventbus/EventBus$LoggingHandler.h"

namespace com {
namespace google {
namespace common {
namespace eventbus {

void EventBus$LoggingHandler::handleException(std::exception exception, SubscriberExceptionContext context) {
    // TODO: Implement handleException
}

Logger EventBus$LoggingHandler::logger(SubscriberExceptionContext context) {
    // TODO: Implement logger
    return nullptr;
}

std::string EventBus$LoggingHandler::message(SubscriberExceptionContext context) {
    // TODO: Implement message
    return "";
}

} // namespace eventbus
} // namespace common
} // namespace google
} // namespace com
