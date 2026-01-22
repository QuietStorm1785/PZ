#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/impl/RuntimeBuiltinLeafInfoImpl/StringImpl.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallingContext.h"
#include "java/net/URI.h"
#include "java/net/URISyntaxException.h"
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
   RuntimeBuiltinLeafInfoImpl$8(Class type, QName... typeNames) {
      super(type, typeNames);
   }

    URI parse(CharSequence text) {
      try {
         return std::make_shared<URI>(text);
      } catch (URISyntaxException var3) {
         UnmarshallingContext.getInstance().handleError(var3);
    return nullptr;
      }
   }

    std::string print(URI v) {
      return v;
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
