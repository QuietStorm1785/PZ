#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/WhiteSpaceProcessor.h"
#include "com/sun/xml/bind/v2/TODO.h"
#include "com/sun/xml/bind/v2/model/impl/RuntimeBuiltinLeafInfoImpl/StringImpl.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallingContext.h"
#include "java/net/MalformedURLException.h"
#include "java/net/URL.h"
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
   RuntimeBuiltinLeafInfoImpl$7(Class type, QName... typeNames) {
      super(type, typeNames);
   }

    URL parse(CharSequence text) {
      TODO.checkSpec("JSR222 Issue #42");

      try {
         return std::make_shared<URL>(WhiteSpaceProcessor.trim(text));
      } catch (MalformedURLException var3) {
         UnmarshallingContext.getInstance().handleError(var3);
    return nullptr;
      }
   }

    std::string print(URL v) {
      return v.toExternalForm();
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
