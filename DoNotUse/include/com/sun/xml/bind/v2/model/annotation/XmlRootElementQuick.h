#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/annotation/XmlRootElement.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace annotation {


class XmlRootElementQuick : public Quick {
public:
    const XmlRootElement core;

    public XmlRootElementQuick(Locatable upstream, XmlRootElement core) {
      super(upstream);
      this.core = core;
   }

    Annotation getAnnotation() {
      return this.core;
   }

    Quick newInstance(Locatable upstream, Annotation core) {
      return std::make_shared<XmlRootElementQuick>(upstream, (XmlRootElement)core);
   }

   public Class<XmlRootElement> annotationType() {
      return XmlRootElement.class;
   }

    std::string name() {
      return this.core.name();
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
