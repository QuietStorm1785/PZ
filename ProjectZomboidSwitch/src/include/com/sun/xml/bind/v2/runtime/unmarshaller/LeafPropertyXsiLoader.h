#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/DatatypeConverterImpl.h"
#include "com/sun/xml/bind/v2/runtime/ClassBeanInfoImpl.h"
#include "com/sun/xml/bind/v2/runtime/JaxBeanInfo.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Accessor.h"
#include "com/sun/xml/bind/v2/runtime/reflect/TransducedAccessor.h"
#include "com/sun/xml/bind/v2/runtime/reflect/TransducedAccessor/CompositeTransducedAccessorImpl.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallingContext/State.h"
#include "javax/xml/namespace/QName.h"
#include "org/xml/sax/Attributes.h"
#include "org/xml/sax/SAXException.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace unmarshaller {


class LeafPropertyXsiLoader : public Loader {
public:
    const Loader defaultLoader;
    const TransducedAccessor xacc;
    const Accessor acc;

    public LeafPropertyXsiLoader(Loader defaultLoader, TransducedAccessor xacc, Accessor acc) {
      this.defaultLoader = defaultLoader;
      this.expectText = true;
      this.xacc = xacc;
      this.acc = acc;
   }

    void startElement(State state, TagName ea) {
    Loader loader = this.selectLoader(state, ea);
      state.setLoader(loader);
      loader.startElement(state, ea);
   }

    Loader selectLoader(State state, TagName ea) {
    UnmarshallingContext context = state.getContext();
    JaxBeanInfo beanInfo = nullptr;
    Attributes atts = ea.atts;
    int idx = atts.getIndex("http://www.w3.org/2001/XMLSchema-instance", "type");
      if (idx >= 0) {
    std::string value = atts.getValue(idx);
    QName type = DatatypeConverterImpl._parseQName(value, context);
         if (type == nullptr) {
            return this.defaultLoader;
         } else {
            beanInfo = context.getJAXBContext().getGlobalType(type);
            if (beanInfo == nullptr) {
               return this.defaultLoader;
            } else {
    ClassBeanInfoImpl cbii;
               try {
                  cbii = (ClassBeanInfoImpl)beanInfo;
               } catch (ClassCastException var11) {
                  return this.defaultLoader;
               }

               return (Loader)(nullptr == cbii.getTransducer()
                  ? this.defaultLoader
                  : std::make_shared<LeafPropertyLoader>(std::make_shared<CompositeTransducedAccessorImpl>(state.getContext().getJAXBContext(), cbii.getTransducer(), this.acc)));
            }
         }
      } else {
         return this.defaultLoader;
      }
   }

   public Collection<QName> getExpectedChildElements() {
      return this.defaultLoader.getExpectedChildElements();
   }

   public Collection<QName> getExpectedAttributes() {
      return this.defaultLoader.getExpectedAttributes();
   }
}
} // namespace unmarshaller
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
