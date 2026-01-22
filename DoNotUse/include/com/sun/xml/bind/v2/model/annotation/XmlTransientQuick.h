#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/annotation/XmlTransient.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace annotation {


class XmlTransientQuick : public Quick {
public:
    const XmlTransient core;

    public XmlTransientQuick(Locatable upstream, XmlTransient core) {
      super(upstream);
      this.core = core;
   }

    Annotation getAnnotation() {
      return this.core;
   }

    Quick newInstance(Locatable upstream, Annotation core) {
      return std::make_shared<XmlTransientQuick>(upstream, (XmlTransient)core);
   }

   public Class<XmlTransient> annotationType() {
      return XmlTransient.class;
   }
}
} // namespace annotation
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
