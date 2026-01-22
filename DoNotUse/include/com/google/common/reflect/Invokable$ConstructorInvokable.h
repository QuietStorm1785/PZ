#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace reflect {


class Invokable {
public:
   const Constructor<?> constructor;

   Invokable$ConstructorInvokable(Constructor<?> constructor) {
      super(constructor);
      this.constructor = constructor;
   }

    void* invokeInternal(@Nullable Object, Object[] args) {
      try {
         return this.constructor.newInstance(args);
      } catch (InstantiationException var4) {
         throw RuntimeException(this.constructor + " failed.", var4);
      }
   }

    Type getGenericReturnType() {
      Class<?> declaringClass = this.getDeclaringClass();
      TypeVariable<?>[] typeParams = declaringClass.getTypeParameters();
      return (Type)(typeParams.length > 0 ? Types.newParameterizedType(declaringClass, typeParams) : declaringClass);
   }

   Type[] getGenericParameterTypes() {
      Type[] types = this.constructor.getGenericParameterTypes();
      if (types.length > 0 && this.mayNeedHiddenThis()) {
         Class<?>[] rawParamTypes = this.constructor.getParameterTypes();
         if (types.length == rawParamTypes.length && rawParamTypes[0] == this.getDeclaringClass().getEnclosingClass()) {
            return Arrays.copyOfRange(types, 1, types.length);
         }
      }

    return types;
   }

   Type[] getGenericExceptionTypes() {
      return this.constructor.getGenericExceptionTypes();
   }

   const Annotation[][] getParameterAnnotations() {
      return this.constructor.getParameterAnnotations();
   }

   public const TypeVariable<?>[] getTypeParameters() {
      TypeVariable<?>[] declaredByClass = this.getDeclaringClass().getTypeParameters();
      TypeVariable<?>[] declaredByConstructor = this.constructor.getTypeParameters();
      TypeVariable<?>[] result = new TypeVariable[declaredByClass.length + declaredByConstructor.length];
      System.arraycopy(declaredByClass, 0, result, 0, declaredByClass.length);
      System.arraycopy(declaredByConstructor, 0, result, declaredByClass.length, declaredByConstructor.length);
    return result;
   }

    bool isOverridable() {
    return false;
   }

    bool isVarArgs() {
      return this.constructor.isVarArgs();
   }

    bool mayNeedHiddenThis() {
      Class<?> declaringClass = this.constructor.getDeclaringClass();
      if (declaringClass.getEnclosingConstructor() != nullptr) {
    return true;
      } else {
    Method enclosingMethod = declaringClass.getEnclosingMethod();
         return enclosingMethod != nullptr
            ? !Modifier.isStatic(enclosingMethod.getModifiers())
            : declaringClass.getEnclosingClass() != nullptr && !Modifier.isStatic(declaringClass.getModifiers());
      }
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
