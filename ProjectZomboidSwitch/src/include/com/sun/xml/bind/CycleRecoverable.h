#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/CycleRecoverable/Context.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {


class CycleRecoverable {
public:
    virtual ~CycleRecoverable() = default;
    void* onCycleDetected(Context var1);
}
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
