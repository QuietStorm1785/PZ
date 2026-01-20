#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/runtime/RuntimeNonElement.h"
#include "com/sun/xml/bind/v2/runtime/Transducer.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class RuntimeAnyTypeImpl : public AnyTypeImpl {
public:
    static const RuntimeNonElement theInstance = std::make_shared<RuntimeAnyTypeImpl>();

    private RuntimeAnyTypeImpl() {
      super(Utils.REFLECTION_NAVIGATOR);
   }

   public <V> Transducer<V> getTransducer() {
    return nullptr;
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
