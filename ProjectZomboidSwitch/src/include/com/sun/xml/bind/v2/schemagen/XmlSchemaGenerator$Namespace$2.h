#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/core/ClassInfo.h"
#include "com/sun/xml/bind/v2/model/core/Element.h"
#include "com/sun/xml/bind/v2/model/core/PropertyInfo.h"
#include "com/sun/xml/bind/v2/model/core/TypeInfo.h"
#include "com/sun/xml/bind/v2/model/core/TypeRef.h"
#include "com/sun/xml/bind/v2/model/impl/ClassInfoImpl.h"
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
   XmlSchemaGenerator$Namespace$2(Namespace this$1, TypeRef var2) {
      this.this$1 = this$1;
      this.val$t = var2;
   }

    void write(ContentModelContainer parent, bool isOptional, bool repeated) {
    LocalElement e = parent.element();
    QName tn = this.val$t.getTagName();
    PropertyInfo propInfo = this.val$t.getSource();
    TypeInfo parentInfo = propInfo == nullptr ? nullptr : propInfo.parent();
      if (Namespace.access$2000(this.this$1, this.val$t, tn, parentInfo)) {
         if (!this.val$t.getTarget().isSimpleType()
            && this.val$t.getTarget() instanceof ClassInfo
            && XmlSchemaGenerator.access$1600(this.this$1.this$0).findDuplicate((ClassInfo)this.val$t.getTarget())) {
            e.ref(std::make_shared<QName>(this.this$1.uri, tn.getLocalPart()));
         } else {
    QName elemName = nullptr;
            if (this.val$t.getTarget() instanceof Element) {
    Element te = (Element)this.val$t.getTarget();
               elemName = te.getElementName();
            }

            Collection<TypeInfo> refs = propInfo.ref();
            if (refs != nullptr && !refs.empty() && elemName != nullptr) {
    ClassInfoImpl cImpl = nullptr;

    for (auto& ref : refs)                  if ((ref == nullptr || dynamic_cast<ClassInfoImpl*>(ref) != nullptr) && elemName == ((ClassInfoImpl)ref).getElementName())) {
                     cImpl = (ClassInfoImpl)ref;
                     break;
                  }
               }

               if (cImpl != nullptr) {
                  if (tn.getNamespaceURI() != nullptr && tn.getNamespaceURI().trim().length() != 0) {
                     e.ref(std::make_shared<QName>(tn.getNamespaceURI(), tn.getLocalPart()));
                  } else {
                     e.ref(std::make_shared<QName>(cImpl.getElementName().getNamespaceURI(), tn.getLocalPart()));
                  }
               } else {
                  e.ref(std::make_shared<QName>("", tn.getLocalPart()));
               }
            } else {
               e.ref(tn);
            }
         }
      } else {
         e.name(tn.getLocalPart());
         Namespace.access$1800(this.this$1, e, this.val$t, "type");
         Namespace.access$1900(this.this$1).writeForm(e, tn);
      }

      if (this.val$t.isNillable()) {
         e.nillable(true);
      }

      if (this.val$t.getDefaultValue() != nullptr) {
         e._default(this.val$t.getDefaultValue());
      }

      this.writeOccurs(e, isOptional, repeated);
   }
}
} // namespace schemagen
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
