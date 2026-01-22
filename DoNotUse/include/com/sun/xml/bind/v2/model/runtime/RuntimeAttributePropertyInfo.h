#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/core/AttributePropertyInfo.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace runtime {


class RuntimeAttributePropertyInfo {
public:
    virtual ~RuntimeAttributePropertyInfo() = default;
    RuntimeNonElement getTarget();
}
} // namespace runtime
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
