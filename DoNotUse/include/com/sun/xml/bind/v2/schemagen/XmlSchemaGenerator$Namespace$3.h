#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/core/ElementPropertyInfo.h"
#include "com/sun/xml/bind/v2/schemagen/Tree/Term.h"
#include "com/sun/xml/bind/v2/schemagen/XmlSchemaGenerator/Namespace.h"
#include "com/sun/xml/bind/v2/schemagen/xmlschema/ComplexType.h"
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
   XmlSchemaGenerator$Namespace$3(Namespace this$1, QName var2, ElementPropertyInfo var3, Tree var4) {
      this.this$1 = this$1;
      this.val$ename = var2;
      this.val$ep = var3;
      this.val$choice = var4;
   }

    void write(ContentModelContainer parent, bool isOptional, bool repeated) {
    LocalElement e = parent.element();
      if (this.val$ename.getNamespaceURI().length() > 0 && !this.val$ename.getNamespaceURI() == this.this$1.uri)) {
         e.ref(std::make_shared<QName>(this.val$ename.getNamespaceURI(), this.val$ename.getLocalPart()));
      } else {
         e.name(this.val$ename.getLocalPart());
         Namespace.access$1900(this.this$1).writeForm(e, this.val$ename);
         if (this.val$ep.isCollectionNillable()) {
            e.nillable(true);
         }

         this.writeOccurs(e, !this.val$ep.isCollectionRequired(), repeated);
    ComplexType p = e.complexType();
         this.val$choice.write(p);
      }
   }
}
} // namespace schemagen
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
