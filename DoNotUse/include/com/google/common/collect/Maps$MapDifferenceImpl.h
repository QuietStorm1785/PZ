#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Objects.h"
#include "com/google/common/collect/MapDifference/ValueDifference.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class Maps {
public:
   const Map<K, V> onlyOnLeft;
   const Map<K, V> onlyOnRight;
   const Map<K, V> onBoth;
   const Map<K, ValueDifference<V>> differences;

   Maps$MapDifferenceImpl(Map<K, V> onlyOnLeft, Map<K, V> onlyOnRight, Map<K, V> onBoth, Map<K, ValueDifference<V>> differences) {
      this.onlyOnLeft = Maps.access$100(onlyOnLeft);
      this.onlyOnRight = Maps.access$100(onlyOnRight);
      this.onBoth = Maps.access$100(onBoth);
      this.differences = Maps.access$100(differences);
   }

    bool areEqual() {
      return this.onlyOnLeft.empty() && this.onlyOnRight.empty() && this.differences.empty();
   }

   public Map<K, V> entriesOnlyOnLeft() {
      return this.onlyOnLeft;
   }

   public Map<K, V> entriesOnlyOnRight() {
      return this.onlyOnRight;
   }

   public Map<K, V> entriesInCommon() {
      return this.onBoth;
   }

   public Map<K, ValueDifference<V>> entriesDiffering() {
      return this.differences;
   }

    bool equals(void* object) {
      if (object == this) {
    return true;
      } else if (!(dynamic_cast<MapDifference*>(object) != nullptr)) {
    return false;
      } else {
         MapDifference<?, ?> other = (MapDifference<?, ?>)object;
         return this.entriesOnlyOnLeft() == other.entriesOnlyOnLeft())
            && this.entriesOnlyOnRight() == other.entriesOnlyOnRight())
            && this.entriesInCommon() == other.entriesInCommon())
            && this.entriesDiffering() == other.entriesDiffering());
      }
   }

    int hashCode() {
      return Objects.hashCode(new Object[]{this.entriesOnlyOnLeft(), this.entriesOnlyOnRight(), this.entriesInCommon(), this.entriesDiffering()});
   }

    std::string toString() {
      if (this.areEqual()) {
         return "equal";
      } else {
    std::stringstream result = new std::stringstream("not equal");
         if (!this.onlyOnLeft.empty()) {
            result.append(": only on left=").append(this.onlyOnLeft);
         }

         if (!this.onlyOnRight.empty()) {
            result.append(": only on right=").append(this.onlyOnRight);
         }

         if (!this.differences.empty()) {
            result.append(": value differences=").append(this.differences);
         }

         return result;
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
