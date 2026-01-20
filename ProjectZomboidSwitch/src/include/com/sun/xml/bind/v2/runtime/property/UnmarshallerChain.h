#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/JAXBContextImpl.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace property {


class UnmarshallerChain {
public:
    int offset = 0;
    const JAXBContextImpl context;

    public UnmarshallerChain(JAXBContextImpl context) {
      this.context = context;
   }

    int allocateOffset() {
      return this.offset++;
   }

    int getScopeSize() {
      return this.offset;
   }
}
} // namespace property
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
