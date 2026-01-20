#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/impl/RuntimeBuiltinLeafInfoImpl/PcdataImpl.h"
#include "com/sun/xml/bind/v2/runtime/XMLSerializer.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/Base64Data.h"
#include "javax/xml/namespace/QName.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class RuntimeBuiltinLeafInfoImpl {
public:
   RuntimeBuiltinLeafInfoImpl$15(Class type, QName... typeNames) {
      super(type, typeNames);
   }

   public byte[] parse(CharSequence text) {
      return RuntimeBuiltinLeafInfoImpl.access$100(text);
   }

    Base64Data print(byte[] v) {
    XMLSerializer w = XMLSerializer.getInstance();
    Base64Data bd = std::make_shared<Base64Data>();
    std::string mimeType = w.getXMIMEContentType();
      bd.set(v, mimeType);
    return bd;
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
