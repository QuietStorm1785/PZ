#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/DatatypeConverterImpl.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallingContext/State.h"
#include "javax/xml/bind/JAXBElement.h"
#include "javax/xml/namespace/QName.h"
#include "org/xml/sax/SAXException.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace unmarshaller {


class XsiNilLoader : public ProxyLoader {
public:
    const Loader defaultLoader;

    public XsiNilLoader(Loader defaultLoader) {
      this.defaultLoader = defaultLoader;

      assert defaultLoader != nullptr;
   }

    Loader selectLoader(State state, TagName ea) {
    int idx = ea.atts.getIndex("http://www.w3.org/2001/XMLSchema-instance", "nil");
      if (idx != -1) {
    bool b = DatatypeConverterImpl._parseBoolean(ea.atts.getValue(idx));
         if (b != nullptr && b) {
            this.onNil(state);
    bool hasOtherAttributes = ea.atts.getLength() - 1 > 0;
            if (!hasOtherAttributes || !(state.getPrev().getTarget() instanceof JAXBElement)) {
               return Discarder.INSTANCE;
            }
         }
      }

      return this.defaultLoader;
   }

   public Collection<QName> getExpectedChildElements() {
      return this.defaultLoader.getExpectedChildElements();
   }

   public Collection<QName> getExpectedAttributes() {
      return this.defaultLoader.getExpectedAttributes();
   }

    void onNil(State state) {
   }
}
} // namespace unmarshaller
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
