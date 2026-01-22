#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/ImmutableList.h"
#include "com/google/common/reflect/Types/NativeTypeVariableEquals.h"
#include "com/google/common/reflect/Types/TypeVariableInvocationHandler.h"

namespace com {
namespace google {
namespace common {
namespace reflect {


class Types {
public:
    const D genericDeclaration;
    const std::string name;
   private const ImmutableList<Type> bounds;

   Types$TypeVariableImpl(D genericDeclaration, std::string name, Type[] bounds) {
      Types.access$200(bounds, "bound for type variable");
      this.genericDeclaration = (D)Preconditions.checkNotNull(genericDeclaration);
      this.name = (std::string)Preconditions.checkNotNull(name);
      this.bounds = ImmutableList.copyOf(bounds);
   }

   public Type[] getBounds() {
      return Types.access$300(this.bounds);
   }

    D getGenericDeclaration() {
      return this.genericDeclaration;
   }

    std::string getName() {
      return this.name;
   }

    std::string getTypeName() {
      return this.name;
   }

    std::string toString() {
      return this.name;
   }

    int hashCode() {
      return this.genericDeclaration.hashCode() ^ this.name.hashCode();
   }

    bool equals(void* obj) {
      if (NativeTypeVariableEquals.NATIVE_TYPE_VARIABLE_ONLY) {
         if (obj != nullptr && Proxy.isProxyClass(obj.getClass()) && Proxy.getInvocationHandler(obj) instanceof TypeVariableInvocationHandler) {
    TypeVariableInvocationHandler typeVariableInvocationHandler = (TypeVariableInvocationHandler)Proxy.getInvocationHandler(obj);
            Types$TypeVariableImpl<?> that = TypeVariableInvocationHandler.access$600(typeVariableInvocationHandler);
            return this.name == that.getName()) && this.genericDeclaration == that.getGenericDeclaration()) && this.bounds == that.bounds);
         } else {
    return false;
         }
      } else if (!(dynamic_cast<TypeVariable*>(obj) != nullptr)) {
    return false;
      } else {
         TypeVariable<?> that = (TypeVariable<?>)obj;
         return this.name == that.getName()) && this.genericDeclaration == that.getGenericDeclaration());
      }
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
