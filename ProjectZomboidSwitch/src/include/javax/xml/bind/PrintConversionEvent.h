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

class PrintConversionEvent {
public:
    virtual ~PrintConversionEvent() = default;
}
} // namespace bind
} // namespace xml
} // namespace javax
