#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/core/WildcardMode.h"
#include "com/sun/xml/bind/v2/schemagen/Tree/Term.h"
#include "com/sun/xml/bind/v2/schemagen/XmlSchemaGenerator/Namespace.h"
#include "com/sun/xml/bind/v2/schemagen/xmlschema/Any.h"
#include "com/sun/xml/bind/v2/schemagen/xmlschema/ContentModelContainer.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace schemagen {


class XmlSchemaGenerator {
public:
   XmlSchemaGenerator$Namespace$5(Namespace this$1, WildcardMode var2) {
      this.this$1 = this$1;
      this.val$wc = var2;
   }

    void write(ContentModelContainer parent, bool isOptional, bool repeated) {
    Any any = parent.any();
    std::string pcmode = XmlSchemaGenerator.access$2200(this.val$wc);
      if (pcmode != nullptr) {
         any.processContents(pcmode);
      }

      any.namespace("##other");
      this.writeOccurs(any, isOptional, repeated);
   }
}
} // namespace schemagen
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
