#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace google {
namespace common {
namespace base {

class CharMatcher {
public:
   private const Predicate<? super char> predicate;

   CharMatcher$ForPredicate(Predicate<? super char> predicate) {
      this.predicate = (Predicate<? super char>)Preconditions.checkNotNull(predicate);
   }

    bool matches(char c) {
      return this.predicate.apply(c);
   }

    bool apply(char character) {
      return this.predicate.apply(Preconditions.checkNotNull(character));
   }

    std::string toString() {
      return "CharMatcher.forPredicate(" + this.predicate + ")";
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
