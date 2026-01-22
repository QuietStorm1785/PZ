#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/istack/NotNull.h"
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


class FilterTransducer {
public:
   protected const Transducer<T> core;

    protected FilterTransducer(Transducer<T> core) {
      this.core = core;
   }

    bool useNamespace() {
      return this.core.useNamespace();
   }

    void declareNamespace(T o, XMLSerializer w) {
      this.core.declareNamespace(o, w);
   }

    CharSequence print(@NotNull T) {
      return this.core.print(o);
   }

    T parse(CharSequence lexical) {
      return (T)this.core.parse(lexical);
   }

    void writeText(XMLSerializer w, T o, const std::string& fieldName) {
      this.core.writeText(w, o, fieldName);
   }

    void writeLeafElement(XMLSerializer w, Name tagName, T o, const std::string& fieldName) {
      this.core.writeLeafElement(w, tagName, o, fieldName);
   }

    QName getTypeName(T instance) {
    return nullptr;
   }
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
