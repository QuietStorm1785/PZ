#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Suppliers/ExpiringMemoizingSupplier.h"
#include "com/google/common/base/Suppliers/MemoizingSupplier.h"
#include "com/google/common/base/Suppliers/SupplierComposition.h"
#include "com/google/common/base/Suppliers/SupplierFunction.h"
#include "com/google/common/base/Suppliers/SupplierFunctionImpl.h"
#include "com/google/common/base/Suppliers/SupplierOfInstance.h"
#include "com/google/common/base/Suppliers/ThreadSafeSupplier.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace base {


class Suppliers {
public:
    private Suppliers() {
   }

   public static <F, T> Supplier<T> compose(Function<? super F, T> function, Supplier<F> supplier) {
      Preconditions.checkNotNull(function);
      Preconditions.checkNotNull(supplier);
      return std::make_shared<SupplierComposition>(function, supplier);
   }

   public static <T> Supplier<T> memoize(Supplier<T> delegate) {
      return (Supplier<T>)(dynamic_cast<MemoizingSupplier*>(delegate) != nullptr ? delegate : std::make_shared<MemoizingSupplier>((Supplier)Preconditions.checkNotNull(delegate)));
   }

   public static <T> Supplier<T> memoizeWithExpiration(Supplier<T> delegate, long duration, TimeUnit unit) {
      return std::make_shared<ExpiringMemoizingSupplier>(delegate, duration, unit);
   }

   public static <T> Supplier<T> ofInstance(@Nullable T instance) {
      return std::make_shared<SupplierOfInstance>(instance);
   }

   public static <T> Supplier<T> synchronizedSupplier(Supplier<T> delegate) {
      return std::make_shared<ThreadSafeSupplier>((Supplier)Preconditions.checkNotNull(delegate));
   }

   public static <T> Function<Supplier<T>, T> supplierFunction() {
      SupplierFunction<T> sf = SupplierFunctionImpl.INSTANCE;
    return sf;
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
