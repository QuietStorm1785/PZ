#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/ClassFactory.h"
#include "javax/xml/bind/ValidationEventHandler.h"
#include "javax/xml/bind/ValidationEventLocator.h"
#include "javax/xml/bind/annotation/adapters/XmlAdapter.h"
#include "javax/xml/bind/helpers/ValidationEventImpl.h"
#include "org/xml/sax/ErrorHandler.h"
#include "org/xml/sax/SAXException.h"
#include "org/xml/sax/SAXParseException.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {


class Coordinator {
public:
   private const std::unordered_map<Class<? : public XmlAdapter>, XmlAdapter> adapters = std::make_unique<std::unordered_map<>>();
   private static const ThreadLocal<Coordinator> activeTable = std::make_unique<ThreadLocal<>>();
    Coordinator old;

    XmlAdapter putAdapter(Class<? extends, XmlAdapter a) {
    return a = = nullptr ? this.adapters.remove(c) : this.adapters.put(c, a);
   }

   public const <T : public XmlAdapter> T getAdapter(Class<T> key) {
    T v = (T)key.cast(this.adapters.get(key));
      if (v == nullptr) {
         v = (T)ClassFactory.create(key);
         this.putAdapter(key, v);
      }

    return v;
   }

   public <T : public XmlAdapter> boolean containsAdapter(Class<T> type) {
      return this.adapters.containsKey(type);
   }

    void pushCoordinator() {
      this.old = activeTable.get();
      activeTable.set(this);
   }

    void popCoordinator() {
      if (this.old != nullptr) {
         activeTable.set(this.old);
      } else {
         activeTable.remove();
      }

      this.old = nullptr;
   }

    static Coordinator _getInstance() {
      return activeTable.get();
   }

   protected abstract ValidationEventLocator getLocation();

    void error(SAXParseException exception) {
      this.propagateEvent(1, exception);
   }

    void warning(SAXParseException exception) {
      this.propagateEvent(0, exception);
   }

    void fatalError(SAXParseException exception) {
      this.propagateEvent(2, exception);
   }

    void propagateEvent(int severity, SAXParseException saxException) {
    ValidationEventImpl ve = std::make_shared<ValidationEventImpl>(severity, saxException.getMessage(), this.getLocation());
    std::exception e = saxException.getException();
      if (e != nullptr) {
         ve.setLinkedException(e);
      } else {
         ve.setLinkedException(saxException);
      }

    bool result = this.handleEvent(ve);
      if (!result) {
    throw saxException;
      }
   }
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
