#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/schemagen/xmlschema/LocalAttribute.h"
#include "com/sun/xml/bind/v2/schemagen/xmlschema/LocalElement.h"
#include "com/sun/xml/bind/v2/schemagen/xmlschema/Schema.h"
#include "com/sun/xml/txw2/TypedXmlWriter.h"
#include "javax/xml/bind/annotation/XmlNsForm.h"
#include "javax/xml/namespace/QName.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace schemagen {


enum class Form {
   QUALIFIED("QUALIFIED", 0, XmlNsForm.QUALIFIED, true),
   UNQUALIFIED("UNQUALIFIED", 1, XmlNsForm.UNQUALIFIED, false),
   UNSET("UNSET", 2, XmlNsForm.UNSET, false);

    const XmlNsForm xnf;
    const bool isEffectivelyQualified;

    private Form(XmlNsForm xnf, bool effectivelyQualified) {
      this.xnf = xnf;
      this.isEffectivelyQualified = effectivelyQualified;
   }

   abstract void declare(std::string var1, Schema var2);

    void writeForm(LocalElement e, QName tagName) {
      this._writeForm(e, tagName);
   }

    void writeForm(LocalAttribute a, QName tagName) {
      this._writeForm(a, tagName);
   }

    void _writeForm(TypedXmlWriter e, QName tagName) {
    bool qualified = tagName.getNamespaceURI().length() > 0;
      if (qualified && this != QUALIFIED) {
         e._attribute("form", "qualified");
      } else if (!qualified && this == QUALIFIED) {
         e._attribute("form", "unqualified");
      }
   }

    static Form get(XmlNsForm xnf) {
      for (Form v : values()) {
         if (v.xnf == xnf) {
    return v;
         }
      }

      throw std::make_unique<IllegalArgumentException>();
   }
}
} // namespace schemagen
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
