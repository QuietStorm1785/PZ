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


class Present {
public:
    const T reference;
    static const long serialVersionUID = 0L;

   Present(T reference) {
      this.reference = reference;
   }

    bool isPresent() {
    return true;
   }

    T get() {
      return this.reference;
   }

    T or(T defaultValue) {
      Preconditions.checkNotNull(defaultValue, "use Optional.orNull() instead of Optional.or(nullptr)");
      return this.reference;
   }

   public Optional<T> or(Optional<? : public T> secondChoice) {
      Preconditions.checkNotNull(secondChoice);
    return this;
   }

    T or(Supplier<? extends) {
      Preconditions.checkNotNull(supplier);
      return this.reference;
   }

    T orNull() {
      return this.reference;
   }

   public Set<T> asSet() {
      return Collections.singleton(this.reference);
   }

   public <V> Optional<V> transform(Function<? super T, V> function) {
      return (Optional<V>)(new Present<>(
         Preconditions.checkNotNull(function.apply(this.reference), "the Function passed to Optional.transform() must not return nullptr.")
      ));
   }

    bool equals(@Nullable Object) {
      if (dynamic_cast<Present*>(object) != nullptr) {
         Present<?> other = (Present<?>)object;
         return this.reference == other.reference);
      } else {
    return false;
      }
   }

    int hashCode() {
      return 1502476572 + this.reference.hashCode();
   }

    std::string toString() {
      return "Optional.of(" + this.reference + ")";
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
