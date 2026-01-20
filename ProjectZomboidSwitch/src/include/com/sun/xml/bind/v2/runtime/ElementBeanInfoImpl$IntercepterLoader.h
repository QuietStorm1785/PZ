#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/unmarshaller/Intercepter.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/Loader.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/TagName.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallingContext.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallingContext/State.h"
#include "javax/xml/bind/JAXBElement.h"
#include "org/xml/sax/SAXException.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {


class ElementBeanInfoImpl {
public:
    const Loader core;

   public ElementBeanInfoImpl$IntercepterLoader(ElementBeanInfoImpl var1, Loader core) {
      this.this$0 = var1;
      this.core = core;
   }

    void startElement(State state, TagName ea) {
      state.setLoader(this.core);
      state.setIntercepter(this);
    UnmarshallingContext context = state.getContext();
    void* child = context.getOuterPeer();
      if (child != nullptr && this.this$0.jaxbType != child.getClass()) {
         child = nullptr;
      }

      if (child != nullptr) {
         this.this$0.reset((JAXBElement)child, context);
      }

      if (child == nullptr) {
         child = context.createInstance(this.this$0);
      }

      this.fireBeforeUnmarshal(this.this$0, child, state);
      context.recordOuterPeer(child);
    State p = state.getPrev();
      p.setBackup(p.getTarget());
      p.setTarget(child);
      this.core.startElement(state, ea);
   }

    void* intercept(State state, void* o) {
    JAXBElement e = (JAXBElement)state.getTarget();
      state.setTarget(state.getBackup());
      state.setBackup(nullptr);
      if (state.isNil()) {
         e.setNil(true);
         state.setNil(false);
      }

      if (o != nullptr) {
         e.setValue(o);
      }

      this.fireAfterUnmarshal(this.this$0, e, state);
    return e;
   }
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
