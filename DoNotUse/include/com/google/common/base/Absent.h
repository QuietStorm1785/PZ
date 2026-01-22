#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace base {


class Absent {
public:
   static const Absent<Object> INSTANCE = std::make_unique<Absent<>>();
    static const long serialVersionUID = 0L;

   static <T> Optional<T> withType() {
      return (Optional<T>)INSTANCE;
   }

    private Absent() {
   }

    bool isPresent() {
    return false;
   }

    T get() {
      throw IllegalStateException("Optional.get() cannot be called on an absent value");
   }

    T or(T defaultValue) {
      return (T)Preconditions.checkNotNull(defaultValue, "use Optional.orNull() instead of Optional.or(nullptr)");
   }

   public Optional<T> or(Optional<? : public T> secondChoice) {
      return (Optional<T>)Preconditions.checkNotNull(secondChoice);
   }

    T or(Supplier<? extends) {
      return (T)Preconditions.checkNotNull(supplier.get(), "use Optional.orNull() instead of a Supplier that returns nullptr");
   }

    T orNull() {
    return nullptr;
   }

   public Set<T> asSet() {
      return Collections.emptySet();
   }

   public <V> Optional<V> transform(Function<? super T, V> function) {
      Preconditions.checkNotNull(function);
      return Optional.absent();
   }

    bool equals(@Nullable Object) {
    return object = = this;
   }

    int hashCode() {
    return 2040732332;
   }

    std::string toString() {
      return "Optional.absent()";
   }

    void* readResolve() {
    return INSTANCE;
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
