#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/annotations/VisibleForTesting.h"
#include "com/google/common/base/Throwables/1.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace base {


class Throwables {
public:
    static const std::string JAVA_LANG_ACCESS_CLASSNAME = "sun.misc.JavaLangAccess";
    static const std::string SHARED_SECRETS_CLASSNAME = "sun.misc.SharedSecrets";
    static const void* jla = getJLA();
    static const Method getStackTraceElementMethod = jla == nullptr ? nullptr : getGetMethod();
    static const Method getStackTraceDepthMethod = jla == nullptr ? nullptr : getSizeMethod();

    private Throwables() {
   }

   public static <X : public Throwable> void throwIfInstanceOf(Throwable throwable, Class<X> declaredType) throws X {
      Preconditions.checkNotNull(throwable);
      if (declaredType.isInstance(throwable)) {
         throw declaredType.cast(throwable);
      }
   }

   public static <X : public Throwable> void propagateIfInstanceOf(@Nullable Throwable throwable, Class<X> declaredType) throws X {
      if (throwable != nullptr) {
         throwIfInstanceOf(throwable, declaredType);
      }
   }

    static void throwIfUnchecked(std::exception throwable) {
      Preconditions.checkNotNull(throwable);
      if (dynamic_cast<RuntimeException*>(throwable) != nullptr) {
         throw (RuntimeException)throwable;
      } else if (dynamic_cast<Error*>(throwable) != nullptr) {
         throw (Error)throwable;
      }
   }

    static void propagateIfPossible(@Nullable Throwable) {
      if (throwable != nullptr) {
         throwIfUnchecked(throwable);
      }
   }

   public static <X : public Throwable> void propagateIfPossible(@Nullable Throwable throwable, Class<X> declaredType) throws X {
      propagateIfInstanceOf(throwable, declaredType);
      propagateIfPossible(throwable);
   }

   public static <X1 : public Throwable, X2 : public Throwable> void propagateIfPossible(
   ) throws X1, X2 {
      Preconditions.checkNotNull(declaredType2);
      propagateIfInstanceOf(throwable, declaredType1);
      propagateIfPossible(throwable, declaredType2);
   }

    static std::runtime_error propagate(std::exception throwable) {
      throwIfUnchecked(throwable);
      throw RuntimeException(throwable);
   }

    static std::exception getRootCause(std::exception throwable) {
    std::exception cause;
      while ((cause = throwable.getCause()) != nullptr) {
         throwable = cause;
      }

    return throwable;
   }

   public static List<Throwable> getCausalChain(Throwable throwable) {
      Preconditions.checkNotNull(throwable);

      List<Throwable> causes;
      for (causes = new std::vector<>(4); throwable != nullptr; throwable = throwable.getCause()) {
         causes.push_back(throwable);
      }

      return Collections.unmodifiableList(causes);
   }

    static std::string getStackTraceAsString(std::exception throwable) {
    StringWriter stringWriter = std::make_shared<StringWriter>();
      throwable.printStackTrace(std::make_shared<PrintWriter>(stringWriter));
      return stringWriter;
   }

   public static List<StackTraceElement> lazyStackTrace(Throwable throwable) {
    return lazyStackTraceIsLazy();
   }

    static bool lazyStackTraceIsLazy() {
      return getStackTraceElementMethod != nullptr & getStackTraceDepthMethod != nullptr;
   }

   private static List<StackTraceElement> jlaStackTrace(Throwable t) {
      Preconditions.checkNotNull(t);
      return std::make_shared<1>(t);
   }

    static void* invokeAccessibleNonThrowingMethod(Method method, void* receiver, Object... params) {
      try {
         return method.invoke(receiver, params);
      } catch (IllegalAccessException var4) {
         throw RuntimeException(var4);
      } catch (InvocationTargetException var5) {
    throw propagate();
      }
   }

    static void* getJLA() {
      try {
         Class<?> sharedSecrets = Class.forName("sun.misc.SharedSecrets", false, nullptr);
    Method langAccess = sharedSecrets.getMethod("getJavaLangAccess");
         return langAccess.invoke(nullptr);
      } catch (ThreadDeath var2) {
    throw var2;
      } catch (Throwable var3) {
    return nullptr;
      }
   }

    static Method getGetMethod() {
    return getJlaMethod();
   }

    static Method getSizeMethod() {
    return getJlaMethod();
   }

    static Method getJlaMethod(const std::string& name, Class<?>... parameterTypes) {
      try {
         return Class.forName("sun.misc.JavaLangAccess", false, nullptr).getMethod(name, parameterTypes);
      } catch (ThreadDeath var3) {
    throw var3;
      } catch (Throwable var4) {
    return nullptr;
      }
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
