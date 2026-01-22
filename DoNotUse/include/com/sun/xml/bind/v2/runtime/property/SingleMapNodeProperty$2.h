#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/unmarshaller/Loader.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/TagName.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallingContext/State.h"
#include "javax/xml/namespace/QName.h"
#include "org/xml/sax/SAXException.h"
#include <algorithm>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace property {


class SingleMapNodeProperty {
public:
   SingleMapNodeProperty$2(SingleMapNodeProperty this$0, boolean expectText) {
      super(expectText);
      this.this$0 = this$0;
   }

    void startElement(State state, TagName ea) {
      state.setTarget(new Object[2]);
   }

    void leaveElement(State state, TagName ea) {
      Object[] keyValue = (Object[])state.getTarget();
    std::unordered_map map = (Map)state.getPrev().getTarget();
      map.put(keyValue[0], keyValue[1]);
   }

    void childElement(State state, TagName ea) {
      if (ea.matches(SingleMapNodeProperty.access$600(this.this$0))) {
         state.setLoader(SingleMapNodeProperty.access$700(this.this$0));
         state.setReceiver(SingleMapNodeProperty.access$800());
      } else if (ea.matches(SingleMapNodeProperty.access$900(this.this$0))) {
         state.setLoader(SingleMapNodeProperty.access$1000(this.this$0));
         state.setReceiver(SingleMapNodeProperty.access$1100());
      } else {
         super.childElement(state, ea);
      }
   }

   public Collection<QName> getExpectedChildElements() {
      return Arrays.asList(SingleMapNodeProperty.access$600(this.this$0).toQName(), SingleMapNodeProperty.access$900(this.this$0).toQName());
   }
}
} // namespace property
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
