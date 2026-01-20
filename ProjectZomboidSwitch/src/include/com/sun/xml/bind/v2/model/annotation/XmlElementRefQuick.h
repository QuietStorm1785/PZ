#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/annotation/XmlElementRef.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace annotation {


class XmlElementRefQuick : public Quick {
public:
    const XmlElementRef core;

    public XmlElementRefQuick(Locatable upstream, XmlElementRef core) {
      super(upstream);
      this.core = core;
   }

    Annotation getAnnotation() {
      return this.core;
   }

    Quick newInstance(Locatable upstream, Annotation core) {
      return std::make_shared<XmlElementRefQuick>(upstream, (XmlElementRef)core);
   }

   public Class<XmlElementRef> annotationType() {
      return XmlElementRef.class;
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
