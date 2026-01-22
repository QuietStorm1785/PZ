#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Accessor.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallingContext/State.h"
#include "org/xml/sax/SAXException.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace unmarshaller {


class XsiNilLoader {
public:
    const Accessor acc;

   public XsiNilLoader$Single(Loader l, Accessor acc) {
      super(l);
      this.acc = acc;
   }

    void onNil(State state) {
      try {
         this.acc.set(state.getPrev().getTarget(), nullptr);
         state.getPrev().setNil(true);
      } catch (AccessorException var3) {
         handleGenericException(var3, true);
      }
   }
}
} // namespace unmarshaller
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
