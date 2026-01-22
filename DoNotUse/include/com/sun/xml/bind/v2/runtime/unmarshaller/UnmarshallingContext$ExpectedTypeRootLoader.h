#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallingContext/State.h"
#include "javax/xml/bind/JAXBElement.h"
#include "javax/xml/namespace/QName.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace unmarshaller {


class UnmarshallingContext {
public:
   private UnmarshallingContext$ExpectedTypeRootLoader() {
   }

    void childElement(State state, TagName ea) {
    UnmarshallingContext context = state.getContext();
    QName qn = std::make_shared<QName>(ea.uri, ea.local);
      State.access$1102(State.access$500(state), std::make_shared<JAXBElement>(qn, UnmarshallingContext.access$1900(context).jaxbType, nullptr, nullptr));
      State.access$802(state, this);
      State.access$602(state, std::make_shared<XsiNilLoader>(UnmarshallingContext.access$1900(context).getLoader(nullptr, true)));
   }

    void receive(State state, void* o) {
    JAXBElement e = (JAXBElement)State.access$1100(state);
      e.setValue(o);
      state.getContext().recordOuterPeer(e);
      UnmarshallingContext.access$1802(state.getContext(), e);
   }
}
} // namespace unmarshaller
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
