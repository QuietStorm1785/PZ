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

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class RuntimeBuiltinLeafInfoImpl {
public:
   RuntimeBuiltinLeafInfoImpl$9(Class type, QName... typeNames) {
      super(type, typeNames);
   }

    Class parse(CharSequence text) {
      TODO.checkSpec("JSR222 Issue #42");

      try {
    std::string name = WhiteSpaceProcessor.trim(text);
    ClassLoader cl = UnmarshallingContext.getInstance().classLoader;
         if (cl == nullptr) {
            cl = Thread.currentThread().getContextClassLoader();
         }

         return cl != nullptr ? cl.loadClass(name) : Class.forName(name);
      } catch (ClassNotFoundException var4) {
         UnmarshallingContext.getInstance().handleError(var4);
    return nullptr;
      }
   }

    std::string print(Class v) {
      return v.getName();
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
