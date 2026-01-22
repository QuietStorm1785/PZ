#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/istack/NotNull.h"
#include "com/sun/istack/Pool/Impl.h"
#include "javax/xml/bind/Unmarshaller.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {


class JAXBContextImpl {
public:
   JAXBContextImpl$2(JAXBContextImpl this$0) {
      this.this$0 = this$0;
   }

    Unmarshaller create() {
      return this.this$0.createUnmarshaller();
   }
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
