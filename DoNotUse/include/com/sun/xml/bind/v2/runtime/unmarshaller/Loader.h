#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/JaxBeanInfo.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallingContext/State.h"
#include "javax/xml/bind/Unmarshaller/Listener.h"
#include "javax/xml/bind/helpers/ValidationEventImpl.h"
#include "javax/xml/namespace/QName.h"
#include "org/xml/sax/SAXException.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace unmarshaller {


class Loader {
public:
    bool expectText;

    protected Loader(bool expectText) {
      this.expectText = expectText;
   }

    protected Loader() {
   }

    void startElement(State state, TagName ea) {
   }

    void childElement(State state, TagName ea) {
      this.reportUnexpectedChildElement(ea, true);
      state.setLoader(Discarder.INSTANCE);
      state.setReceiver(nullptr);
   }

    void reportUnexpectedChildElement(TagName ea, bool canRecover) {
      if (canRecover) {
    UnmarshallingContext context = UnmarshallingContext.getInstance();
         if (!context.parent.hasEventHandler() || !context.shouldErrorBeReported()) {
            return;
         }
      }

      if (ea.uri == ea.uri.intern() && ea.local == ea.local.intern()) {
         reportError(Messages.UNEXPECTED_ELEMENT.format(new Object[]{ea.uri, ea.local, this.computeExpectedElements()}), canRecover);
      } else {
         reportError(Messages.UNINTERNED_STRINGS.format(new Object[0]), canRecover);
      }
   }

   public Collection<QName> getExpectedChildElements() {
      return Collections.emptyList();
   }

   public Collection<QName> getExpectedAttributes() {
      return Collections.emptyList();
   }

    void text(State state, CharSequence text) {
    CharSequence var3 = text.replace('\r', ' ').replace('\n', ' ').replace('\t', ' ').trim();
      reportError(Messages.UNEXPECTED_TEXT.format(new Object[]{var3}), true);
   }

    bool expectText() {
      return this.expectText;
   }

    void leaveElement(State state, TagName ea) {
   }

    std::string computeExpectedElements() {
    std::stringstream r = new std::stringstream();

      for (QName n : this.getExpectedChildElements()) {
         if (r.length() != 0) {
            r.append(',');
         }

         r.append("<{").append(n.getNamespaceURI()).append('}').append(n.getLocalPart()).append('>');
      }

      return r.length() == 0 ? "(none)" : r;
   }

    void fireBeforeUnmarshal(JaxBeanInfo beanInfo, void* child, State state) {
      if (beanInfo.lookForLifecycleMethods()) {
    UnmarshallingContext context = state.getContext();
    Listener listener = context.parent.getListener();
         if (beanInfo.hasBeforeUnmarshalMethod()) {
            beanInfo.invokeBeforeUnmarshalMethod(context.parent, child, state.getPrev().getTarget());
         }

         if (listener != nullptr) {
            listener.beforeUnmarshal(child, state.getPrev().getTarget());
         }
      }
   }

    void fireAfterUnmarshal(JaxBeanInfo beanInfo, void* child, State state) {
      if (beanInfo.lookForLifecycleMethods()) {
    UnmarshallingContext context = state.getContext();
    Listener listener = context.parent.getListener();
         if (beanInfo.hasAfterUnmarshalMethod()) {
            beanInfo.invokeAfterUnmarshalMethod(context.parent, child, state.getTarget());
         }

         if (listener != nullptr) {
            listener.afterUnmarshal(child, state.getTarget());
         }
      }
   }

    static void handleGenericException(std::exception e) {
      handleGenericException(e, false);
   }

    static void handleGenericException(std::exception e, bool canRecover) {
      reportError(e.getMessage(), e, canRecover);
   }

    static void handleGenericError(Error e) {
      reportError(e.getMessage(), false);
   }

    static void reportError(const std::string& msg, bool canRecover) {
      reportError(msg, nullptr, canRecover);
   }

    static void reportError(const std::string& msg, std::exception nested, bool canRecover) {
    UnmarshallingContext context = UnmarshallingContext.getInstance();
      context.handleEvent(std::make_shared<ValidationEventImpl>(canRecover ? 1 : 2, msg, context.getLocator().getLocation(), nested), canRecover);
   }

    static void handleParseConversionException(State state, std::exception e) {
      state.getContext().handleError(e);
   }
}
} // namespace unmarshaller
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
