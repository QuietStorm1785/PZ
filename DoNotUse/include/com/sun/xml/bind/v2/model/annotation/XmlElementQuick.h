#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/annotation/XmlElement.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace annotation {


class XmlElementQuick : public Quick {
public:
    const XmlElement core;

    public XmlElementQuick(Locatable upstream, XmlElement core) {
      super(upstream);
      this.core = core;
   }

    Annotation getAnnotation() {
      return this.core;
   }

    Quick newInstance(Locatable upstream, Annotation core) {
      return std::make_shared<XmlElementQuick>(upstream, (XmlElement)core);
   }

   public Class<XmlElement> annotationType() {
      return XmlElement.class;
   }

    std::string name() {
      return this.core.name();
   }

    Class type() {
      return this.core.type();
   }

    std::string namespace() {
      return this.core.namespace();
   }

    std::string defaultValue() {
      return this.core.defaultValue();
   }

    bool required() {
      return this.core.required();
   }

    bool nillable() {
      return this.core.nillable();
   }
}
} // namespace annotation
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
