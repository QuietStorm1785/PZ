#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallingContext/State.h"
#include "org/xml/sax/SAXException.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace unmarshaller {


class DefaultValueLoaderDecorator : public Loader {
public:
    const Loader l;
    const std::string defaultValue;

    public DefaultValueLoaderDecorator(Loader l, const std::string& defaultValue) {
      this.l = l;
      this.defaultValue = defaultValue;
   }

    void startElement(State state, TagName ea) {
      if (state.getElementDefaultValue() == nullptr) {
         state.setElementDefaultValue(this.defaultValue);
      }

      state.setLoader(this.l);
      this.l.startElement(state, ea);
   }
}
} // namespace unmarshaller
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
