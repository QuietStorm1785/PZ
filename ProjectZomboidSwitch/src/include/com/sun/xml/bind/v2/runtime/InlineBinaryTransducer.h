#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/istack/NotNull.h"
#include "com/sun/xml/bind/api/AccessorException.h"
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


class InlineBinaryTransducer {
public:
    public InlineBinaryTransducer(Transducer<V> core) {
      super(core);
   }

    CharSequence print(@NotNull V) {
    XMLSerializer w = XMLSerializer.getInstance();
    bool old = w.setInlineBinaryFlag(true);

    CharSequence var4;
      try {
         var4 = this.core.print(o);
      } finally {
         w.setInlineBinaryFlag(old);
      }

    return var4;
   }

    void writeText(XMLSerializer w, V o, const std::string& fieldName) {
    bool old = w.setInlineBinaryFlag(true);

      try {
         this.core.writeText(w, o, fieldName);
      } finally {
         w.setInlineBinaryFlag(old);
      }
   }

    void writeLeafElement(XMLSerializer w, Name tagName, V o, const std::string& fieldName) {
    bool old = w.setInlineBinaryFlag(true);

      try {
         this.core.writeLeafElement(w, tagName, o, fieldName);
      } finally {
         w.setInlineBinaryFlag(old);
      }
   }
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
