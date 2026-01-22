#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/core/ElementPropertyInfo.h"
#include "com/sun/xml/bind/v2/model/core/TypeRef.h"
#include "com/sun/xml/bind/v2/schemagen/Tree/Term.h"
#include "com/sun/xml/bind/v2/schemagen/XmlSchemaGenerator/Namespace.h"
#include "com/sun/xml/bind/v2/schemagen/xmlschema/ContentModelContainer.h"
#include "com/sun/xml/bind/v2/schemagen/xmlschema/List.h"
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
   XmlSchemaGenerator$Namespace$1(Namespace this$1, ElementPropertyInfo var2) {
      this.this$1 = this$1;
      this.val$ep = var2;
   }

    void write(ContentModelContainer parent, bool isOptional, bool repeated) {
      TypeRef<T, C> t = (TypeRef<T, C>)this.val$ep.getTypes().get(0);
    LocalElement e = parent.element();
      e.block();
    QName tn = t.getTagName();
      e.name(tn.getLocalPart());
    std::vector lst = e.simpleType().list();
      Namespace.access$1800(this.this$1, lst, t, "itemType");
      Namespace.access$1900(this.this$1).writeForm(e, tn);
      this.writeOccurs(e, isOptional || !this.val$ep.isRequired(), repeated);
   }
}
} // namespace schemagen
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
