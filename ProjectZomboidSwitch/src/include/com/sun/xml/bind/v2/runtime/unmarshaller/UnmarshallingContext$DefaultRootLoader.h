#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/JaxBeanInfo.h"
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


class UnmarshallingContext {
public:
   private UnmarshallingContext$DefaultRootLoader() {
   }

    void childElement(State state, TagName ea) {
    Loader loader = state.getContext().selectRootLoader(state, ea);
      if (loader != nullptr) {
         State.access$602(state, loader);
         State.access$802(state, this);
      } else {
    JaxBeanInfo beanInfo = XsiTypeLoader.parseXsiType(state, ea, nullptr);
         if (beanInfo == nullptr) {
            this.reportUnexpectedChildElement(ea, false);
         } else {
            State.access$602(state, beanInfo.getLoader(nullptr, false));
            State.access$1702(State.access$500(state), std::make_shared<JAXBElement>(ea.createQName(), Object.class, nullptr));
            State.access$802(state, this);
         }
      }
   }

   public Collection<QName> getExpectedChildElements() {
      return UnmarshallingContext.getInstance().getJAXBContext().getValidRootNames();
   }

    void receive(State state, void* o) {
      if (State.access$1700(state) != nullptr) {
         ((JAXBElement)State.access$1700(state)).setValue(o);
         o = State.access$1700(state);
      }

      if (State.access$700(state)) {
         ((JAXBElement)o).setNil(true);
      }

      UnmarshallingContext.access$1802(state.getContext(), o);
   }
}
} // namespace unmarshaller
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
