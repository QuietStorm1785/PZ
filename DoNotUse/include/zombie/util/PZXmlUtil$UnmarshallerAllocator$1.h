#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/Unmarshaller/Listener.h"
#include "zombie/util/PZXmlUtil/UnmarshallerAllocator.h"

namespace zombie {
namespace util {


class PZXmlUtil {
public:
   PZXmlUtil$UnmarshallerAllocator$1(UnmarshallerAllocator var1) {
      this.this$0 = var1;
   }

    void beforeUnmarshal(void* var1, void* var2) {
      super.beforeUnmarshal(var1, var2);
   }
}
} // namespace util
} // namespace zombie
