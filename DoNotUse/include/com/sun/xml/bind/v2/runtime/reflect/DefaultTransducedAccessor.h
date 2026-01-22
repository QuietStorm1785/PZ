#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/runtime/Name.h"
#include "com/sun/xml/bind/v2/runtime/XMLSerializer.h"
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
namespace reflect {


class DefaultTransducedAccessor {
public:
   public abstract std::string print(T var1) throws AccessorException, SAXException;

    void writeLeafElement(XMLSerializer w, Name tagName, T o, const std::string& fieldName) {
      w.leafElement(tagName, this.print(o), fieldName);
   }

    void writeText(XMLSerializer w, T o, const std::string& fieldName) {
      w.text(this.print(o), fieldName);
   }
}
} // namespace reflect
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
