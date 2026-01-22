#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/DatatypeConverterImpl.h"
#include "com/sun/xml/bind/v2/model/impl/RuntimeBuiltinLeafInfoImpl/StringImpl.h"
#include "com/sun/xml/bind/v2/runtime/XMLSerializer.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallingContext.h"
#include "javax/xml/namespace/QName.h"
#include "org/xml/sax/SAXException.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class RuntimeBuiltinLeafInfoImpl {
public:
   RuntimeBuiltinLeafInfoImpl$24(Class type, QName... typeNames) {
      super(type, typeNames);
   }

    QName parse(CharSequence text) {
      try {
         return DatatypeConverterImpl._parseQName(text, UnmarshallingContext.getInstance());
      } catch (IllegalArgumentException var3) {
         UnmarshallingContext.getInstance().handleError(var3);
    return nullptr;
      }
   }

    std::string print(QName v) {
      return DatatypeConverterImpl._printQName(v, XMLSerializer.getInstance().getNamespaceContext());
   }

    bool useNamespace() {
    return true;
   }

    void declareNamespace(QName v, XMLSerializer w) {
      w.getNamespaceContext().declareNamespace(v.getNamespaceURI(), v.getPrefix(), false);
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
