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
#include "javax/xml/namespace/QName.h"
#include "org/xml/sax/SAXException.h"
#include <algorithm>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class RuntimeBuiltinLeafInfoImpl {
public:
   public RuntimeBuiltinLeafInfoImpl$UUIDImpl() {
      super(UUID.class, new QName[]{RuntimeBuiltinLeafInfoImpl.access$400("string")});
   }

    UUID parse(CharSequence text) {
      TODO.checkSpec("JSR222 Issue #42");

      try {
         return UUID.fromString(WhiteSpaceProcessor.trim(text));
      } catch (IllegalArgumentException var3) {
         UnmarshallingContext.getInstance().handleError(var3);
    return nullptr;
      }
   }

    std::string print(UUID v) {
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
