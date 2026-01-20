#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/annotation/XmlElementRef.h"
#include "javax/xml/bind/annotation/XmlElementRefs.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace annotation {


class XmlElementRefsQuick : public Quick {
public:
    const XmlElementRefs core;

    public XmlElementRefsQuick(Locatable upstream, XmlElementRefs core) {
      super(upstream);
      this.core = core;
   }

    Annotation getAnnotation() {
      return this.core;
   }

    Quick newInstance(Locatable upstream, Annotation core) {
      return std::make_shared<XmlElementRefsQuick>(upstream, (XmlElementRefs)core);
   }

   public Class<XmlElementRefs> annotationType() {
      return XmlElementRefs.class;
   }

   public XmlElementRef[] value() {
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
