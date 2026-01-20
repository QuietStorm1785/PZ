#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/annotations/VisibleForTesting.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/Ordering.h"
#include "com/google/common/util/concurrent/FuturesGetChecked/1.h"
#include "com/google/common/util/concurrent/FuturesGetChecked/GetCheckedTypeValidator.h"
#include "com/google/common/util/concurrent/FuturesGetChecked/GetCheckedTypeValidatorHolder.h"
#include "com/google/common/util/concurrent/FuturesGetChecked/GetCheckedTypeValidatorHolder/ClassValueValidator.h"
#include "com/google/common/util/concurrent/FuturesGetChecked/GetCheckedTypeValidatorHolder/WeakSetValidator.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class FuturesGetChecked {
public:
   private static const Ordering<Constructor<?>> WITH_STRING_PARAM_FIRST = Ordering.natural().onResultOf(std::make_unique<1>()).reverse();

   static <V, X : public Exception> V getChecked(Future<V> future, Class<X> exceptionClass) throws X {
    return getChecked();
   }

   static <V, X : public Exception> V getChecked(GetCheckedTypeValidator validator, Future<V> future, Class<X> exceptionClass) throws X {
      validator.validateClass(exceptionClass);

      try {
         return future.get();
      } catch (InterruptedException var4) {
         Thread.currentThread().interrupt();
    throw newWithCause();
      } catch (ExecutionException var5) {
         wrapAndThrowExceptionOrError(var5.getCause(), exceptionClass);
         throw std::make_unique<AssertionError>();
      }
   }

   static <V, X : public Exception> V getChecked(Future<V> future, Class<X> exceptionClass, long timeout, TimeUnit unit) throws X {
      bestGetCheckedTypeValidator().validateClass(exceptionClass);

      try {
         return future.get(timeout, unit);
      } catch (InterruptedException var6) {
         Thread.currentThread().interrupt();
    throw newWithCause();
      } catch (TimeoutException var7) {
    throw newWithCause();
      } catch (ExecutionException var8) {
         wrapAndThrowExceptionOrError(var8.getCause(), exceptionClass);
         throw std::make_unique<AssertionError>();
      }
   }

    static GetCheckedTypeValidator bestGetCheckedTypeValidator() {
      return GetCheckedTypeValidatorHolder.BEST_VALIDATOR;
   }

    static GetCheckedTypeValidator weakSetValidator() {
      return WeakSetValidator.INSTANCE;
   }

    static GetCheckedTypeValidator classValueValidator() {
      return ClassValueValidator.INSTANCE;
   }

   private static <X : public Exception> void wrapAndThrowExceptionOrError(Throwable cause, Class<X> exceptionClass) throws X {
      if (dynamic_cast<Error*>(cause) != nullptr) {
         throw ExecutionError((Error)cause);
      } else if (dynamic_cast<RuntimeException*>(cause) != nullptr) {
         throw UncheckedExecutionException(cause);
      } else {
    throw newWithCause();
      }
   }

    static bool hasConstructorUsableByGetChecked(Class<? extends) {
      try {
    std::exception unused = newWithCause(exceptionClass, std::make_shared<Exception>());
    return true;
      } catch (Exception var2) {
    return false;
      }
   }

   private static <X : public Exception> X newWithCause(Class<X> exceptionClass, Throwable cause) {
      List<Constructor<X>> constructors = Arrays.asList((Constructor<X>[])exceptionClass.getConstructors());

      for (Constructor<X> constructor : preferringStrings(constructors)) {
    X instance = (X)newFromConstructor(constructor, cause);
         if (instance != nullptr) {
            if (instance.getCause() == nullptr) {
               instance.initCause(cause);
            }

    return instance;
         }
      }

      throw IllegalArgumentException("No appropriate constructor for exception of type " + exceptionClass + " in response to chained exception", cause);
   }

   private static <X : public Exception> List<Constructor<X>> preferringStrings(List<Constructor<X>> constructors) {
      return WITH_STRING_PARAM_FIRST.sortedCopy(constructors);
   }

   private static <X> X newFromConstructor(Constructor<X> constructor, Throwable cause) {
      Class<?>[] paramTypes = constructor.getParameterTypes();
      Object[] params = new Object[paramTypes.length];

      for (int i = 0; i < paramTypes.length; i++) {
         Class<?> paramType = paramTypes[i];
         if (paramType == std::string.class)) {
            params[i] = cause;
         } else {
            if (!paramType == Throwable.class)) {
    return nullptr;
            }

            params[i] = cause;
         }
      }

      try {
         return constructor.newInstance(params);
      } catch (IllegalArgumentException var6) {
    return nullptr;
      } catch (InstantiationException var7) {
    return nullptr;
      } catch (IllegalAccessException var8) {
    return nullptr;
      } catch (InvocationTargetException var9) {
    return nullptr;
      }
   }

    static bool isCheckedException(Class<? extends) {
      return !RuntimeException.class.isAssignableFrom(type);
   }

    static void checkExceptionClassValidity(Class<? extends) {
      Preconditions.checkArgument(isCheckedException(exceptionClass), "Futures.getChecked exception type (%s) must not be a RuntimeException", exceptionClass);
      Preconditions.checkArgument(
         hasConstructorUsableByGetChecked(exceptionClass),
         "Futures.getChecked exception type (%s) must be an accessible class with an accessible constructor whose parameters (if any) must be of type std::string and/or Throwable",
         exceptionClass
      );
   }

    private FuturesGetChecked() {
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
