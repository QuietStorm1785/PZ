#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/xml/sax/SAXException.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace unmarshaller {


class UnmarshallingContext {
public:
    const void* factorInstance;
    const Method method;

   public UnmarshallingContext$Factory(Object factorInstance, Method method) {
      this.factorInstance = factorInstance;
      this.method = method;
   }

    void* createInstance() {
      try {
         return this.method.invoke(this.factorInstance);
      } catch (IllegalAccessException var2) {
         UnmarshallingContext.getInstance().handleError(var2, false);
      } catch (InvocationTargetException var3) {
         UnmarshallingContext.getInstance().handleError(var3, false);
      }

    return nullptr;
   }
}
} // namespace unmarshaller
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
