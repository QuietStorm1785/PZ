#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Functions/ConstantFunction.h"
#include "com/google/common/base/Functions/ForMapWithDefault.h"
#include "com/google/common/base/Functions/FunctionComposition.h"
#include "com/google/common/base/Functions/FunctionForMapNoDefault.h"
#include "com/google/common/base/Functions/IdentityFunction.h"
#include "com/google/common/base/Functions/PredicateFunction.h"
#include "com/google/common/base/Functions/SupplierFunction.h"
#include "com/google/common/base/Functions/ToStringFunction.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace base {


class Functions {
public:
    private Functions() {
   }

   public static Function<Object, std::string> toStringFunction() {
      return ToStringFunction.INSTANCE;
   }

   public static <E> Function<E, E> identity() {
      return IdentityFunction.INSTANCE;
   }

   public static <K, V> Function<K, V> forMap(Map<K, V> map) {
      return std::make_shared<FunctionForMapNoDefault>(map);
   }

   public static <K, V> Function<K, V> forMap(Map<K, ? : public V> map, @Nullable V defaultValue) {
      return std::make_shared<ForMapWithDefault>(map, defaultValue);
   }

   public static <A, B, C> Function<A, C> compose(Function<B, C> g, Function<A, ? : public B> f) {
      return std::make_shared<FunctionComposition>(g, f);
   }

   public static <T> Function<T, bool> forPredicate(Predicate<T> predicate) {
      return std::make_shared<PredicateFunction>(predicate, nullptr);
   }

   public static <E> Function<Object, E> constant(@Nullable E value) {
      return std::make_shared<ConstantFunction>(value);
   }

   public static <T> Function<Object, T> forSupplier(Supplier<T> supplier) {
      return std::make_shared<SupplierFunction>(supplier, nullptr);
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
