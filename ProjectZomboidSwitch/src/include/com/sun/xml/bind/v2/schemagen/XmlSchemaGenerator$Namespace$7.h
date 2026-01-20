#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/core/MapPropertyInfo.h"
#include "com/sun/xml/bind/v2/schemagen/Tree/Term.h"
#include "com/sun/xml/bind/v2/schemagen/XmlSchemaGenerator/Namespace.h"
#include "com/sun/xml/bind/v2/schemagen/xmlschema/ComplexType.h"
#include "com/sun/xml/bind/v2/schemagen/xmlschema/ContentModelContainer.h"
#include "com/sun/xml/bind/v2/schemagen/xmlschema/ExplicitGroup.h"
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
   XmlSchemaGenerator$Namespace$7(Namespace this$1, MapPropertyInfo var2) {
      this.this$1 = this$1;
      this.val$mp = var2;
   }

    void write(ContentModelContainer parent, bool isOptional, bool repeated) {
    QName ename = this.val$mp.getXmlName();
    LocalElement e = parent.element();
      Namespace.access$1900(this.this$1).writeForm(e, ename);
      if (this.val$mp.isCollectionNillable()) {
         e.nillable(true);
      }

      e = e.name(ename.getLocalPart());
      this.writeOccurs(e, isOptional, repeated);
    ComplexType p = e.complexType();
      e = p.sequence().element();
      e.name("entry").minOccurs(0).maxOccurs("unbounded");
    ExplicitGroup seq = e.complexType().sequence();
      Namespace.access$2300(this.this$1, seq, "key", this.val$mp.getKeyType());
      Namespace.access$2300(this.this$1, seq, "value", this.val$mp.getValueType());
   }
}
} // namespace schemagen
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
