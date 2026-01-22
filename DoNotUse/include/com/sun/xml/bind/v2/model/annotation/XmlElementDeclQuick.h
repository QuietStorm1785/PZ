#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/annotation/XmlElementDecl.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace annotation {


class XmlElementDeclQuick : public Quick {
public:
    const XmlElementDecl core;

    public XmlElementDeclQuick(Locatable upstream, XmlElementDecl core) {
      super(upstream);
      this.core = core;
   }

    Annotation getAnnotation() {
      return this.core;
   }

    Quick newInstance(Locatable upstream, Annotation core) {
      return std::make_shared<XmlElementDeclQuick>(upstream, (XmlElementDecl)core);
   }

   public Class<XmlElementDecl> annotationType() {
      return XmlElementDecl.class;
   }

    std::string name() {
      return this.core.name();
   }

    Class scope() {
      return this.core.scope();
   }

    std::string namespace() {
      return this.core.namespace();
   }

    std::string defaultValue() {
      return this.core.defaultValue();
   }

    std::string substitutionHeadNamespace() {
      return this.core.substitutionHeadNamespace();
   }

    std::string substitutionHeadName() {
      return this.core.substitutionHeadName();
   }
}
} // namespace annotation
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
