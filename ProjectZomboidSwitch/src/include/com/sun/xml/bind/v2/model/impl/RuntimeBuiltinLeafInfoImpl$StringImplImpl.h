#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/impl/RuntimeBuiltinLeafInfoImpl/StringImpl.h"
#include "com/sun/xml/bind/v2/runtime/Name.h"
#include "com/sun/xml/bind/v2/runtime/XMLSerializer.h"
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
namespace model {
namespace impl {


class RuntimeBuiltinLeafInfoImpl {
public:
   public RuntimeBuiltinLeafInfoImpl$StringImplImpl(Class type, QName[] typeNames) {
      super(type, typeNames);
   }

    std::string parse(CharSequence text) {
      return text;
   }

    std::string print(const std::string& s) {
    return s;
   }

    void writeText(XMLSerializer w, const std::string& o, const std::string& fieldName) {
      w.text(o, fieldName);
   }

    void writeLeafElement(XMLSerializer w, Name tagName, const std::string& o, const std::string& fieldName) {
      w.leafElement(tagName, o, fieldName);
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
