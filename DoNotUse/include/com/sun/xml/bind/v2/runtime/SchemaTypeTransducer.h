#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/AccessorException.h"
#include "javax/xml/namespace/QName.h"
#include "javax/xml/stream/XMLStreamException.h"
#include "org/xml/sax/SAXException.h"
#include <fstream>
#include <iostream>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {


class SchemaTypeTransducer {
public:
    const QName schemaType;

    public SchemaTypeTransducer(Transducer<V> core, QName schemaType) {
      super(core);
      this.schemaType = schemaType;
   }

    CharSequence print(V o) {
    XMLSerializer w = XMLSerializer.getInstance();
    QName old = w.setSchemaType(this.schemaType);

    CharSequence var4;
      try {
         var4 = this.core.print(o);
      } finally {
         w.setSchemaType(old);
      }

    return var4;
   }

    void writeText(XMLSerializer w, V o, const std::string& fieldName) {
    QName old = w.setSchemaType(this.schemaType);

      try {
         this.core.writeText(w, o, fieldName);
      } finally {
         w.setSchemaType(old);
      }
   }

    void writeLeafElement(XMLSerializer w, Name tagName, V o, const std::string& fieldName) {
    QName old = w.setSchemaType(this.schemaType);

      try {
         this.core.writeLeafElement(w, tagName, o, fieldName);
      } finally {
         w.setSchemaType(old);
      }
   }
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
