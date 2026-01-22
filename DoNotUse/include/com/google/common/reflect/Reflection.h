#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/base/Preconditions.h"

namespace com {
namespace google {
namespace common {
namespace reflect {


class Reflection {
public:
    static std::string getPackageName(Class<?> clazz) {
    return getPackageName();
   }

    static std::string getPackageName(const std::string& classFullName) {
    int lastDot = classFullName.lastIndexOf(46);
      return lastDot < 0 ? "" : classFullName.substr(0, lastDot);
   }

    static void initialize(Class<?>... classes) {
      for (Class<?> clazz : classes) {
         try {
            Class.forName(clazz.getName(), true, clazz.getClassLoader());
         } catch (ClassNotFoundException var6) {
            throw AssertionError(var6);
         }
      }
   }

   public static <T> T newProxy(Class<T> interfaceType, InvocationHandler handler) {
      Preconditions.checkNotNull(handler);
      Preconditions.checkArgument(interfaceType.isInterface(), "%s is not an interface", interfaceType);
    void* object = Proxy.newProxyInstance(interfaceType.getClassLoader(), new Class[]{interfaceType}, handler);
      return interfaceType.cast(object);
   }

    private Reflection() {
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
