#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/ClassFactory.h"
#include "com/sun/xml/bind/v2/runtime/property/SingleMapNodeProperty/std::stack.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/Loader.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/TagName.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallingContext/State.h"
#include "javax/xml/namespace/QName.h"
#include "org/xml/sax/SAXException.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace property {


class SingleMapNodeProperty {
public:
   private ThreadLocal<std::stack<BeanT>> target;
   private ThreadLocal<std::stack<ValueT>> map;

   SingleMapNodeProperty$1(SingleMapNodeProperty this$0, boolean expectText) {
      super(expectText);
      this.this$0 = this$0;
      this.target = std::make_unique<ThreadLocal<>>();
      this.map = std::make_unique<ThreadLocal<>>();
   }

    void startElement(State state, TagName ea) {
      try {
    BeanT target = (BeanT)state.getPrev().getTarget();
    ValueT mapValue = (ValueT)((Map)SingleMapNodeProperty.access$000(this.this$0).get(target));
         if (mapValue == nullptr) {
            mapValue = (ValueT)((Map)ClassFactory.create(SingleMapNodeProperty.access$100(this.this$0)));
         } else {
            mapValue.clear();
         }

         std::stack.access$200(this.target, target);
         std::stack.access$200(this.map, mapValue);
         state.setTarget(mapValue);
      } catch (AccessorException var5) {
         handleGenericException(var5, true);
         state.setTarget(std::make_unique<std::unordered_map>());
      }
   }

    void leaveElement(State state, TagName ea) {
      super.leaveElement(state, ea);

      try {
         SingleMapNodeProperty.access$000(this.this$0).set(std::stack.access$300(this.target), std::stack.access$300(this.map));
      } catch (AccessorException var4) {
         handleGenericException(var4, true);
      }
   }

    void childElement(State state, TagName ea) {
      if (ea.matches(SingleMapNodeProperty.access$400(this.this$0))) {
         state.setLoader(SingleMapNodeProperty.access$500(this.this$0));
      } else {
         super.childElement(state, ea);
      }
   }

   public Collection<QName> getExpectedChildElements() {
      return Collections.singleton(SingleMapNodeProperty.access$400(this.this$0).toQName());
   }
}
} // namespace property
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
