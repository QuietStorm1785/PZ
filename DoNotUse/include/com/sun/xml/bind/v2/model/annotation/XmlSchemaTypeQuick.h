#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/annotation/XmlSchemaType.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace annotation {


class XmlSchemaTypeQuick : public Quick {
public:
    const XmlSchemaType core;

    public XmlSchemaTypeQuick(Locatable upstream, XmlSchemaType core) {
      super(upstream);
      this.core = core;
   }

    Annotation getAnnotation() {
      return this.core;
   }

    Quick newInstance(Locatable upstream, Annotation core) {
      return std::make_shared<XmlSchemaTypeQuick>(upstream, (XmlSchemaType)core);
   }

   public Class<XmlSchemaType> annotationType() {
      return XmlSchemaType.class;
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
}
} // namespace annotation
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
