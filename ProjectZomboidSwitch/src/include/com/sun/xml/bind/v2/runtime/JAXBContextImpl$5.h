#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/api/RawAccessor.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Accessor.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {


class JAXBContextImpl {
public:
   JAXBContextImpl$5(JAXBContextImpl this$0, Accessor var2) {
      this.this$0 = this$0;
      this.val$acc = var2;
   }

    void* get(void* bean) {
      return this.val$acc.getUnadapted(bean);
   }

    void set(void* bean, void* value) {
      this.val$acc.setUnadapted(bean, value);
   }
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
