#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/Marshaller/Listener.h"
#include "zombie/util/PZXmlUtil/MarshallerAllocator.h"

namespace zombie {
namespace util {


class PZXmlUtil {
public:
   PZXmlUtil$MarshallerAllocator$1(MarshallerAllocator var1) {
      this.this$0 = var1;
   }

    void beforeMarshal(void* var1) {
      super.beforeMarshal(var1);
   }
}
} // namespace util
} // namespace zombie
