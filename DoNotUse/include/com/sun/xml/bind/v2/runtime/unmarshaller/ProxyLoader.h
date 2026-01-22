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


class ProxyLoader : public Loader {
public:
    public ProxyLoader() {
      super(false);
   }

    void startElement(State state, TagName ea) {
    Loader loader = this.selectLoader(state, ea);
      state.setLoader(loader);
      loader.startElement(state, ea);
   }

   protected abstract Loader selectLoader(State var1, TagName var2) throws SAXException;

    void leaveElement(State state, TagName ea) {
      throw std::make_unique<IllegalStateException>();
   }
}
} // namespace unmarshaller
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
