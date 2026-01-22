#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/runtime/reflect/TransducedAccessor.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallingContext/State.h"
#include "org/xml/sax/SAXException.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace unmarshaller {


class LeafPropertyLoader : public Loader {
public:
    const TransducedAccessor xacc;

    public LeafPropertyLoader(TransducedAccessor xacc) {
      super(true);
      this.xacc = xacc;
   }

    void text(State state, CharSequence text) {
      try {
         this.xacc.parse(state.getPrev().getTarget(), text);
      } catch (AccessorException var4) {
         handleGenericException(var4, true);
      } catch (RuntimeException var5) {
         handleParseConversionException(state, var5);
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
