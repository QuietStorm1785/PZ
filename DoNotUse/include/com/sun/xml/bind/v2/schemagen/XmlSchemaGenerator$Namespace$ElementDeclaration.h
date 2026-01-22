#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/schemagen/XmlSchemaGenerator/Namespace.h"
#include "com/sun/xml/bind/v2/schemagen/xmlschema/Schema.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace schemagen {


class XmlSchemaGenerator {
public:
   XmlSchemaGenerator$Namespace$ElementDeclaration(Namespace this$1) {
      this.this$1 = this$1;
   }

   public abstract boolean equals(Object var1);

   public abstract int hashCode();

   public abstract void writeTo(std::string var1, Schema var2);
}
} // namespace schemagen
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
