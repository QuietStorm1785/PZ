#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/CycleRecoverable/Context.h"
#include "javax/xml/bind/Marshaller.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {


class XMLSerializer {
public:
   XMLSerializer$1(XMLSerializer this$0) {
      this.this$0 = this$0;
   }

    Marshaller getMarshaller() {
      return XMLSerializer.access$000(this.this$0);
   }
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
