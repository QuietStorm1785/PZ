#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/core/ClassInfo.h"
#include "com/sun/xml/bind/v2/model/core/Element.h"
#include "com/sun/xml/bind/v2/model/core/ElementInfo.h"
#include "com/sun/xml/bind/v2/schemagen/Tree/Term.h"
#include "com/sun/xml/bind/v2/schemagen/XmlSchemaGenerator/Namespace.h"
#include "com/sun/xml/bind/v2/schemagen/xmlschema/ContentModelContainer.h"
#include "com/sun/xml/bind/v2/schemagen/xmlschema/LocalElement.h"
#include "javax/xml/namespace/QName.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace schemagen {


class XmlSchemaGenerator {
public:
   XmlSchemaGenerator$Namespace$4(Namespace this$1, Element var2) {
      this.this$1 = this$1;
      this.val$e = var2;
   }

    void write(ContentModelContainer parent, bool isOptional, bool repeated) {
    LocalElement eref = parent.element();
    bool local = false;
    QName en = this.val$e.getElementName();
      if (this.val$e.getScope() != nullptr) {
    bool qualified = en.getNamespaceURI() == this.this$1.uri);
    bool unqualified = en.getNamespaceURI() == "");
         if (qualified || unqualified) {
            if (unqualified) {
               if (Namespace.access$1900(this.this$1).isEffectivelyQualified) {
                  eref.form("unqualified");
               }
            } else if (!Namespace.access$1900(this.this$1).isEffectivelyQualified) {
               eref.form("qualified");
            }

            local = true;
            eref.name(en.getLocalPart());
            if (this.val$dynamic_cast<ClassInfo*>(e) != nullptr) {
               Namespace.access$2100(this.this$1, eref, (ClassInfo)this.val$e, "type");
            } else {
               Namespace.access$2100(this.this$1, eref, ((ElementInfo)this.val$e).getContentType(), "type");
            }
         }
      }

      if (!local) {
         eref.ref(en);
      }

      this.writeOccurs(eref, isOptional, repeated);
   }
}
} // namespace schemagen
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
