#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/runtime/Transducer.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallingContext/State.h"
#include "org/xml/sax/SAXException.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace unmarshaller {


class TextLoader : public Loader {
public:
    const Transducer xducer;

    public TextLoader(Transducer xducer) {
      super(true);
      this.xducer = xducer;
   }

    void text(State state, CharSequence text) {
      try {
         state.setTarget(this.xducer.parse(text));
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
