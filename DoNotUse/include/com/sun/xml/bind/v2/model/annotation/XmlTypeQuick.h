#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/annotation/XmlType.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace annotation {


class XmlTypeQuick : public Quick {
public:
    const XmlType core;

    public XmlTypeQuick(Locatable upstream, XmlType core) {
      super(upstream);
      this.core = core;
   }

    Annotation getAnnotation() {
      return this.core;
   }

    Quick newInstance(Locatable upstream, Annotation core) {
      return std::make_shared<XmlTypeQuick>(upstream, (XmlType)core);
   }

   public Class<XmlType> annotationType() {
      return XmlType.class;
   }

    std::string name() {
      return this.core.name();
   }

    std::string namespace() {
      return this.core.namespace();
   }

   public std::string[] propOrder() {
      return this.core.propOrder();
   }

    Class factoryClass() {
      return this.core.factoryClass();
   }

    std::string factoryMethod() {
      return this.core.factoryMethod();
   }
}
} // namespace annotation
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
