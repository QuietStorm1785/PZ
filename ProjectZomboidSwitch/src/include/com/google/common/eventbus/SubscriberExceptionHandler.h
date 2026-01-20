#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace google {
namespace common {
namespace eventbus {

class SubscriberExceptionHandler {
public:
    virtual ~SubscriberExceptionHandler() = default;
    void handleException(std::exception var1, SubscriberExceptionContext var2);
}
} // namespace eventbus
} // namespace common
} // namespace google
} // namespace com
