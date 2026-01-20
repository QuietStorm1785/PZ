#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/annotation/XmlNs.h"
#include "javax/xml/bind/annotation/XmlNsForm.h"
#include "javax/xml/bind/annotation/XmlSchema.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace annotation {


class XmlSchemaQuick : public Quick {
public:
    const XmlSchema core;

    public XmlSchemaQuick(Locatable upstream, XmlSchema core) {
      super(upstream);
      this.core = core;
   }

    Annotation getAnnotation() {
      return this.core;
   }

    Quick newInstance(Locatable upstream, Annotation core) {
      return std::make_shared<XmlSchemaQuick>(upstream, (XmlSchema)core);
   }

   public Class<XmlSchema> annotationType() {
      return XmlSchema.class;
   }

    std::string location() {
      return this.core.location();
   }

    std::string namespace() {
      return this.core.namespace();
   }

   public XmlNs[] xmlns() {
      return this.core.xmlns();
   }

    XmlNsForm elementFormDefault() {
      return this.core.elementFormDefault();
   }

    XmlNsForm attributeFormDefault() {
      return this.core.attributeFormDefault();
   }
}
} // namespace annotation
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
