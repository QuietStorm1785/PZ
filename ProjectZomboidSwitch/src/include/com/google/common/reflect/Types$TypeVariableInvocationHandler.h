#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/ImmutableMap.h"
#include "com/google/common/collect/ImmutableMap/Builder.h"
#include "com/google/common/reflect/Types/TypeVariableImpl.h"
#include "java/security/AccessControlException.h"

namespace com {
namespace google {
namespace common {
namespace reflect {


class Types {
public:
   private static const ImmutableMap<std::string, Method> typeVariableMethods;
   private const TypeVariableImpl<?> typeVariableImpl;

   Types$TypeVariableInvocationHandler(TypeVariableImpl<?> typeVariableImpl) {
      this.typeVariableImpl = typeVariableImpl;
   }

    void* invoke(void* proxy, Method method, Object[] args) {
    std::string methodName = method.getName();
    Method typeVariableMethod = (Method)typeVariableMethods.get(methodName);
      if (typeVariableMethod == nullptr) {
         throw UnsupportedOperationException(methodName);
      } else {
         try {
            return typeVariableMethod.invoke(this.typeVariableImpl, args);
         } catch (InvocationTargetException var7) {
            throw var7.getCause();
         }
      }
   }

   static {
      Builder<std::string, Method> builder = ImmutableMap.builder();

      for (Method method : TypeVariableImpl.class.getMethods()) {
         if (method.getDeclaringClass() == TypeVariableImpl.class)) {
            try {
               method.setAccessible(true);
            } catch (AccessControlException var6) {
            }

            builder.put(method.getName(), method);
         }
      }

      typeVariableMethods = builder.build();
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
