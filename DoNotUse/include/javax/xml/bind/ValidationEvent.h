#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace javax {
namespace xml {
namespace bind {

class ValidationEvent {
public:
    virtual ~ValidationEvent() = default;
    int WARNING = 0;
    int ERROR = 1;
    int FATAL_ERROR = 2;

    int getSeverity();

    std::string getMessage();

    std::exception getLinkedException();

    ValidationEventLocator getLocator();
}
} // namespace bind
} // namespace xml
} // namespace javax
