#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/core/PropertyInfo.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Accessor.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace runtime {


class RuntimePropertyInfo {
public:
    virtual ~RuntimePropertyInfo() = default;
   Collection<? : public RuntimeTypeInfo> ref();

    Accessor getAccessor();

    bool elementOnlyContent();

    Type getRawType();

    Type getIndividualType();
}
} // namespace runtime
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
