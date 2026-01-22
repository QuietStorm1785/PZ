#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/core/ElementPropertyInfo.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace runtime {


class RuntimeElementPropertyInfo {
public:
    virtual ~RuntimeElementPropertyInfo() = default;
   Collection<? : public RuntimeTypeInfo> ref();

   List<? : public RuntimeTypeRef> getTypes();
}
} // namespace runtime
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
