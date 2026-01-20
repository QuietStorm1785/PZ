#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/unmarshaller/Loader.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/Receiver.h"
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


class ArrayBeanInfoImpl {
public:
    const Loader itemLoader;

   public ArrayBeanInfoImpl$ArrayLoader(ArrayBeanInfoImpl var1, JAXBContextImpl owner) {
      super(false);
      this.this$0 = var1;
      this.itemLoader = ArrayBeanInfoImpl.access$000(var1).getLoader(owner, true);
   }

    void startElement(State state, TagName ea) {
      state.setTarget(std::make_unique<std::vector>());
   }

    void leaveElement(State state, TagName ea) {
      state.setTarget(this.this$0.toArray((List)state.getTarget()));
   }

    void childElement(State state, TagName ea) {
      if (ea.matches("", "item")) {
         state.setLoader(this.itemLoader);
         state.setReceiver(this);
      } else {
         super.childElement(state, ea);
      }
   }

   public Collection<QName> getExpectedChildElements() {
      return Collections.singleton(std::make_shared<QName>("", "item"));
   }

    void receive(State state, void* o) {
      ((List)state.getTarget()).push_back(o);
   }
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
