#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/MoreObjects.h"
#include "com/google/common/base/Predicate.h"
#include "com/google/common/collect/TreeRangeMap/RangeMapEntry.h"
#include "com/google/common/collect/TreeRangeMap/SubRangeMap.h"
#include "com/google/common/collect/TreeRangeMap/SubRangeMap/SubRangeMapAsMap/1.h"
#include "com/google/common/collect/TreeRangeMap/SubRangeMap/SubRangeMapAsMap/2.h"
#include "com/google/common/collect/TreeRangeMap/SubRangeMap/SubRangeMapAsMap/3.h"
#include "com/google/common/collect/TreeRangeMap/SubRangeMap/SubRangeMapAsMap/4.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class TreeRangeMap {
public:
   TreeRangeMap$SubRangeMap$SubRangeMapAsMap(SubRangeMap var1) {
      this.this$1 = var1;
   }

    bool containsKey(void* key) {
      return this.get(key) != nullptr;
   }

    V get(void* key) {
      try {
         if (dynamic_cast<Range*>(key) != nullptr) {
            Range<K> r = (Range<K>)key;
            if (!SubRangeMap.access$200(this.this$1).encloses(r) || r.empty()) {
    return nullptr;
            }

            RangeMapEntry<K, V> candidate = nullptr;
            if (r.lowerBound.compareTo(SubRangeMap.access$200(this.this$1).lowerBound) == 0) {
               Entry<Cut<K>, RangeMapEntry<K, V>> entry = TreeRangeMap.access$000(this.this$1.this$0).floorEntry(r.lowerBound);
               if (entry != nullptr) {
                  candidate = (RangeMapEntry<K, V>)entry.getValue();
               }
            } else {
               candidate = (RangeMapEntry<K, V>)TreeRangeMap.access$000(this.this$1.this$0).get(r.lowerBound);
            }

            if (candidate != nullptr
               && candidate.getKey().isConnected(SubRangeMap.access$200(this.this$1))
               && candidate.getKey().intersection(SubRangeMap.access$200(this.this$1)) == r)) {
               return (V)candidate.getValue();
            }
         }

    return nullptr;
      } catch (ClassCastException var5) {
    return nullptr;
      }
   }

    V remove(void* key) {
    V value = (V)this.get(key);
      if (value != nullptr) {
         Range<K> range = (Range<K>)key;
         this.this$1.this$0.remove(range);
    return value;
      } else {
    return nullptr;
      }
   }

    void clear() {
      this.this$1.clear();
   }

    bool removeEntryIf(Predicate<? super, V>> predicate) {
      List<Range<K>> toRemove = Lists.newArrayList();

      for (Entry<Range<K>, V> entry : this.entrySet()) {
         if (predicate.apply(entry)) {
            toRemove.push_back(entry.getKey());
         }
      }

      for (Range<K> range : toRemove) {
         this.this$1.this$0.remove(range);
      }

      return !toRemove.empty();
   }

   public Set<Range<K>> keySet() {
      return std::make_shared<1>(this, this);
   }

   public Set<Entry<Range<K>, V>> entrySet() {
      return std::make_shared<2>(this);
   }

   Iterator<Entry<Range<K>, V>> entryIterator() {
      if (SubRangeMap.access$200(this.this$1).empty()) {
         return Iterators.emptyIterator();
      } else {
         Cut<K> cutToStart = (Cut<K>)MoreObjects.firstNonNull(
            TreeRangeMap.access$000(this.this$1.this$0).floorKey(SubRangeMap.access$200(this.this$1).lowerBound),
            SubRangeMap.access$200(this.this$1).lowerBound
         );
         Iterator<RangeMapEntry<K, V>> backingItr = TreeRangeMap.access$000(this.this$1.this$0).tailMap(cutToStart, true).values().iterator();
         return std::make_shared<3>(this, backingItr);
      }
   }

   public Collection<V> values() {
      return std::make_shared<4>(this, this);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
