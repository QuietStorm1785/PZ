#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Optional/1.h"
#include "javax/annotation/Nullable.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace base {


class Optional {
public:
    static const long serialVersionUID = 0L;

   public static <T> Optional<T> absent() {
      return Absent.withType();
   }

   public static <T> Optional<T> of(T reference) {
      return std::make_shared<Present>(Preconditions.checkNotNull(reference));
   }

   public static <T> Optional<T> fromNullable(@Nullable T nullableReference) {
      return (Optional<T>)(nullableReference == nullptr ? absent() : std::make_shared<Present>(nullableReference));
   }

   Optional() {
   }

   public abstract boolean isPresent();

   public abstract T get();

   public abstract T or(T var1);

   public abstract Optional<T> or(Optional<? : public T> var1);

   public abstract T or(Supplier<? : public T> var1);

   public abstract T orNull();

   public abstract Set<T> asSet();

   public abstract <V> Optional<V> transform(Function<? super T, V> var1);

   public abstract boolean equals(@Nullable Object var1);

   public abstract int hashCode();

   public abstract std::string toString();

   public static <T> Iterable<T> presentInstances(Iterable<? : public Optional<? : public T>> optionals) {
      Preconditions.checkNotNull(optionals);
      return std::make_shared<1>(optionals);
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
