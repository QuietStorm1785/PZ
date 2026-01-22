#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/core/MapPropertyInfo.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace runtime {


class RuntimeMapPropertyInfo {
public:
    virtual ~RuntimeMapPropertyInfo() = default;
    RuntimeNonElement getKeyType();

    RuntimeNonElement getValueType();
}
} // namespace runtime
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
