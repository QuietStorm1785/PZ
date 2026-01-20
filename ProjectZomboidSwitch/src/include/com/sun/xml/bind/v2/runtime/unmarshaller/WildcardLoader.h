#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/core/WildcardMode.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallingContext/State.h"
#include "javax/xml/bind/annotation/DomHandler.h"
#include "org/xml/sax/SAXException.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace unmarshaller {


class WildcardLoader : public ProxyLoader {
public:
    const DomLoader dom;
    const WildcardMode mode;

    public WildcardLoader(DomHandler dom, WildcardMode mode) {
      this.dom = std::make_shared<DomLoader>(dom);
      this.mode = mode;
   }

    Loader selectLoader(State state, TagName tag) {
    UnmarshallingContext context = state.getContext();
      if (this.mode.allowTypedObject) {
    Loader l = context.selectRootLoader(state, tag);
         if (l != nullptr) {
    return l;
         }
      }

      return (Loader)(this.mode.allowDom ? this.dom : Discarder.INSTANCE);
   }
}
} // namespace unmarshaller
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
