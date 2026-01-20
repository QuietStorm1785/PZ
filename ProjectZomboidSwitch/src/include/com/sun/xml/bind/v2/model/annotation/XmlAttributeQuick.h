#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/annotation/XmlAttribute.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace annotation {


class XmlAttributeQuick : public Quick {
public:
    const XmlAttribute core;

    public XmlAttributeQuick(Locatable upstream, XmlAttribute core) {
      super(upstream);
      this.core = core;
   }

    Annotation getAnnotation() {
      return this.core;
   }

    Quick newInstance(Locatable upstream, Annotation core) {
      return std::make_shared<XmlAttributeQuick>(upstream, (XmlAttribute)core);
   }

   public Class<XmlAttribute> annotationType() {
      return XmlAttribute.class;
   }

    std::string name() {
      return this.core.name();
   }

    std::string namespace() {
      return this.core.namespace();
   }

    bool required() {
      return this.core.required();
   }
}
} // namespace annotation
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
