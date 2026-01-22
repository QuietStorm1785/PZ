#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/core/NonElementRef.h"
#include "com/sun/xml/bind/v2/runtime/Transducer.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace runtime {


class RuntimeNonElementRef {
public:
    virtual ~RuntimeNonElementRef() = default;
    RuntimeNonElement getTarget();

    RuntimePropertyInfo getSource();

    Transducer getTransducer();
}
} // namespace runtime
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
