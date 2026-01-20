#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/unmarshaller/DomLoader/State.h"
#include "javax/xml/bind/annotation/DomHandler.h"
#include "javax/xml/transform/Result.h"
#include "org/xml/sax/SAXException.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace unmarshaller {


class DomLoader {
public:
   private const DomHandler<?, ResultT> dom;

    public DomLoader(ResultT> dom) {
      super(true);
      this.dom = dom;
   }

    void startElement(com.sun.xml.bind.v2.runtime.unmarshaller.UnmarshallingContext.State state, TagName ea) {
    UnmarshallingContext context = state.getContext();
      if (state.getTarget() == nullptr) {
         state.setTarget(std::make_shared<State>(this, context));
      }

      DomLoader<ResultT>.State s = (State)state.getTarget();

      try {
         State.access$100(s, context, context.getNewlyDeclaredPrefixes());
         State.access$200(s).startElement(ea.uri, ea.local, ea.getQname(), ea.atts);
      } catch (SAXException var6) {
         context.handleError(var6);
    throw var6;
      }
   }

    void childElement(com.sun.xml.bind.v2.runtime.unmarshaller.UnmarshallingContext.State state, TagName ea) {
      state.setLoader(this);
      DomLoader<ResultT>.State s = (State)state.getPrev().getTarget();
      s.depth++;
      state.setTarget(s);
   }

    void text(com.sun.xml.bind.v2.runtime.unmarshaller.UnmarshallingContext.State state, CharSequence text) {
      if (text.length() != 0) {
         try {
            DomLoader<ResultT>.State s = (State)state.getTarget();
            State.access$200(s).characters(text.toCharArray(), 0, text.length());
         } catch (SAXException var4) {
            state.getContext().handleError(var4);
    throw var4;
         }
      }
   }

    void leaveElement(com.sun.xml.bind.v2.runtime.unmarshaller.UnmarshallingContext.State state, TagName ea) {
      DomLoader<ResultT>.State s = (State)state.getTarget();
    UnmarshallingContext context = state.getContext();

      try {
         State.access$200(s).endElement(ea.uri, ea.local, ea.getQname());
         State.access$300(s, context.getNewlyDeclaredPrefixes());
      } catch (SAXException var7) {
         context.handleError(var7);
    throw var7;
      }

      if (--s.depth == 0) {
         try {
            State.access$300(s, context.getAllDeclaredPrefixes());
            State.access$200(s).endDocument();
         } catch (SAXException var6) {
            context.handleError(var6);
    throw var6;
         }

         state.setTarget(s.getElement());
      }
   }
}
} // namespace unmarshaller
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
