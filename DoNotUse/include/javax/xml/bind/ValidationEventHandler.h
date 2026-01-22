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

class ValidationEventHandler {
public:
    virtual ~ValidationEventHandler() = default;
    bool handleEvent(ValidationEvent var1);
}
} // namespace bind
} // namespace xml
} // namespace javax
