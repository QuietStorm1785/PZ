#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace reflect {


class AbstractInvocationHandler {
public:
   private static const Object[] NO_ARGS = new Object[0];

    void* invoke(void* proxy, Method method, @Nullable Object[]) {
      if (args == nullptr) {
         args = NO_ARGS;
      }

      if (args.length == 0 && method.getName() == "hashCode")) {
         return this.hashCode();
      } else if (args.length == 1 && method.getName() == "equals") && method.getParameterTypes()[0] == Object.class) {
    void* arg = args[0];
         if (arg == nullptr) {
    return false;
         } else {
    return proxy = = arg ? true : isProxyOfSameInterfaces(arg, proxy.getClass()) && this == Proxy.getInvocationHandler(arg));
         }
      } else {
         return args.length == 0 && method.getName() == "toString") ? this : this.handleInvocation(proxy, method, args);
      }
   }

   protected abstract Object handleInvocation(Object var1, Method var2, Object[] var3) throws Throwable;

    bool equals(void* obj) {
      return super == obj);
   }

    int hashCode() {
      return super.hashCode();
   }

    std::string toString() {
      return super;
   }

    static bool isProxyOfSameInterfaces(void* arg, Class<?> proxyClass) {
      return proxyClass.isInstance(arg)
         || Proxy.isProxyClass(arg.getClass()) && Arrays == (Object[])arg.getClass().getInterfaces(), (Object[])proxyClass.getInterfaces());
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
