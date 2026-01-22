#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/reflect/Accessor.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Lister.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/ChildLoader.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/Loader.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/TagName.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallingContext.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallingContext/State.h"
#include "com/sun/xml/bind/v2/util/QNameMap.h"
#include "javax/xml/namespace/QName.h"
#include "org/xml/sax/SAXException.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace property {


class ArrayERProperty {
public:
    const Accessor acc;
    const Lister lister;
   private const QNameMap<ChildLoader> children;

   public ArrayERProperty$ItemsLoader(Accessor acc, Lister lister, QNameMap<ChildLoader> children) {
      super(false);
      this.acc = acc;
      this.lister = lister;
      this.children = children;
   }

    void startElement(State state, TagName ea) {
    UnmarshallingContext context = state.getContext();
      context.startScope(1);
      state.setTarget(state.getPrev().getTarget());
      context.getScope(0).start(this.acc, this.lister);
   }

    void childElement(State state, TagName ea) {
    ChildLoader child = (ChildLoader)this.children.get(ea.uri, ea.local);
      if (child == nullptr) {
         child = (ChildLoader)this.children.get(StructureLoaderBuilder.CATCH_ALL);
      }

      if (child == nullptr) {
         super.childElement(state, ea);
      } else {
         state.setLoader(child.loader);
         state.setReceiver(child.receiver);
      }
   }

    void leaveElement(State state, TagName ea) {
      state.getContext().endScope(1);
   }

   public Collection<QName> getExpectedChildElements() {
      return this.children.keySet();
   }
}
} // namespace property
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
