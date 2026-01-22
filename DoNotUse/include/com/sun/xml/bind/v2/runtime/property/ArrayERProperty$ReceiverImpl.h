#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/unmarshaller/Receiver.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallingContext/State.h"
#include "org/xml/sax/SAXException.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace property {


class ArrayERProperty {
public:
    const int offset;

   protected ArrayERProperty$ReceiverImpl(ArrayERProperty this$0, int offset) {
      this.this$0 = this$0;
      this.offset = offset;
   }

    void receive(State state, void* o) {
      state.getContext().getScope(this.offset).push_back(this.this$0.acc, this.this$0.lister, o);
   }
}
} // namespace property
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
