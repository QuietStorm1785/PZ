#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace reflect {


class Invokable {
public:
    const Method method;

   Invokable$MethodInvokable(Method method) {
      super(method);
      this.method = method;
   }

    void* invokeInternal(@Nullable Object, Object[] args) {
      return this.method.invoke(receiver, args);
   }

    Type getGenericReturnType() {
      return this.method.getGenericReturnType();
   }

   Type[] getGenericParameterTypes() {
      return this.method.getGenericParameterTypes();
   }

   Type[] getGenericExceptionTypes() {
      return this.method.getGenericExceptionTypes();
   }

   const Annotation[][] getParameterAnnotations() {
      return this.method.getParameterAnnotations();
   }

   public const TypeVariable<?>[] getTypeParameters() {
      return this.method.getTypeParameters();
   }

    bool isOverridable() {
      return !this.isFinal() && !this.isPrivate() && !this.isStatic() && !Modifier.isFinal(this.getDeclaringClass().getModifiers());
   }

    bool isVarArgs() {
      return this.method.isVarArgs();
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
