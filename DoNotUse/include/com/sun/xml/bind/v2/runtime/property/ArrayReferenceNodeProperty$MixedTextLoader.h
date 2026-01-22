#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/unmarshaller/Loader.h"
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


class ArrayReferenceNodeProperty {
public:
    const Receiver recv;

   public ArrayReferenceNodeProperty$MixedTextLoader(Receiver recv) {
      super(true);
      this.recv = recv;
   }

    void text(State state, CharSequence text) {
      if (text.length() != 0) {
         this.recv.receive(state, text);
      }
   }
}
} // namespace property
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
