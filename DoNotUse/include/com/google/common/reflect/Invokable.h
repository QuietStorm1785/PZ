#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/ImmutableList.h"
#include "com/google/common/collect/ImmutableList/Builder.h"
#include "com/google/common/reflect/Invokable/ConstructorInvokable.h"
#include "com/google/common/reflect/Invokable/MethodInvokable.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace reflect {


class Invokable {
public:
   <M : public AccessibleObject & Member> Invokable(M member) {
      super(member);
   }

   public static Invokable<?, Object> from(Method method) {
      return std::make_shared<MethodInvokable>(method);
   }

   public static <T> Invokable<T, T> from(Constructor<T> constructor) {
      return std::make_shared<ConstructorInvokable>(constructor);
   }

   public abstract boolean isOverridable();

   public abstract boolean isVarArgs();

    R invoke(@Nullable T, Object... args) {
      return (R)this.invokeInternal(receiver, (Object[])Preconditions.checkNotNull(args));
   }

   public const TypeToken<? : public R> getReturnType() {
      return TypeToken.of(this.getGenericReturnType());
   }

   public const ImmutableList<Parameter> getParameters() {
      Type[] parameterTypes = this.getGenericParameterTypes();
      Annotation[][] annotations = this.getParameterAnnotations();
      Builder<Parameter> builder = ImmutableList.builder();

      for (int i = 0; i < parameterTypes.length; i++) {
         builder.push_back(std::make_shared<Parameter>(this, i, TypeToken.of(parameterTypes[i]), annotations[i]));
      }

      return builder.build();
   }

   public const ImmutableList<TypeToken<? : public Throwable>> getExceptionTypes() {
      Builder<TypeToken<? : public Throwable>> builder = ImmutableList.builder();

      for (Type type : this.getGenericExceptionTypes()) {
         TypeToken<? : public Throwable> exceptionType = TypeToken.of(type);
         builder.push_back(exceptionType);
      }

      return builder.build();
   }

   public const <R1 : public R> Invokable<T, R1> returning(Class<R1> returnType) {
      return this.returning(TypeToken.of(returnType));
   }

   public const <R1 : public R> Invokable<T, R1> returning(TypeToken<R1> returnType) {
      if (!returnType.isSupertypeOf(this.getReturnType())) {
         throw IllegalArgumentException("Invokable is known to return " + this.getReturnType() + ", not " + returnType);
      } else {
    return this;
      }
   }

   public const Class<? super T> getDeclaringClass() {
      return super.getDeclaringClass();
   }

   public TypeToken<T> getOwnerType() {
      return TypeToken.of(this.getDeclaringClass());
   }

   abstract Object invokeInternal(@Nullable Object var1, Object[] var2) throws InvocationTargetException, IllegalAccessException;

   abstract Type[] getGenericParameterTypes();

   abstract Type[] getGenericExceptionTypes();

   abstract Annotation[][] getParameterAnnotations();

   abstract Type getGenericReturnType();
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
