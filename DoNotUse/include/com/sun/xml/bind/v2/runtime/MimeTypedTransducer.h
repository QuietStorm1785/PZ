#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/AccessorException.h"
#include "javax/activation/MimeType.h"
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


class MimeTypedTransducer {
public:
    const MimeType expectedMimeType;

    public MimeTypedTransducer(Transducer<V> core, MimeType expectedMimeType) {
      super(core);
      this.expectedMimeType = expectedMimeType;
   }

    CharSequence print(V o) {
    XMLSerializer w = XMLSerializer.getInstance();
    MimeType old = w.setExpectedMimeType(this.expectedMimeType);

    CharSequence var4;
      try {
         var4 = this.core.print(o);
      } finally {
         w.setExpectedMimeType(old);
      }

    return var4;
   }

    void writeText(XMLSerializer w, V o, const std::string& fieldName) {
    MimeType old = w.setExpectedMimeType(this.expectedMimeType);

      try {
         this.core.writeText(w, o, fieldName);
      } finally {
         w.setExpectedMimeType(old);
      }
   }

    void writeLeafElement(XMLSerializer w, Name tagName, V o, const std::string& fieldName) {
    MimeType old = w.setExpectedMimeType(this.expectedMimeType);

      try {
         this.core.writeLeafElement(w, tagName, o, fieldName);
      } finally {
         w.setExpectedMimeType(old);
      }
   }
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
