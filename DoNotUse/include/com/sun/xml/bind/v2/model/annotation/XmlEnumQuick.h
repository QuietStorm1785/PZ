#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/annotation/XmlEnum.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace annotation {


class XmlEnumQuick : public Quick {
public:
    const XmlEnum core;

    public XmlEnumQuick(Locatable upstream, XmlEnum core) {
      super(upstream);
      this.core = core;
   }

    Annotation getAnnotation() {
      return this.core;
   }

    Quick newInstance(Locatable upstream, Annotation core) {
      return std::make_shared<XmlEnumQuick>(upstream, (XmlEnum)core);
   }

   public Class<XmlEnum> annotationType() {
      return XmlEnum.class;
   }

    Class value() {
      return this.core.value();
   }
}
} // namespace annotation
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
