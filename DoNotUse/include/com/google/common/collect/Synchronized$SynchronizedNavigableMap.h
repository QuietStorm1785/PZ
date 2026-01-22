#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/annotations/VisibleForTesting.h"
#include "com/google/common/collect/Synchronized/SynchronizedSortedMap.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Synchronized {
public:
   transient NavigableSet<K> descendingKeySet;
   transient NavigableMap<K, V> descendingMap;
   transient NavigableSet<K> navigableKeySet;
    static const long serialVersionUID = 0L;

   Synchronized$SynchronizedNavigableMap(NavigableMap<K, V> delegate, @Nullable Object mutex) {
      super(delegate, mutex);
   }

   NavigableMap<K, V> delegate() {
      return (NavigableMap<K, V>)super.delegate();
   }

   public Entry<K, V> ceilingEntry(K key) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return Synchronized.access$700(this.delegate().ceilingEntry(key), this.mutex);
      }
   }

    K ceilingKey(K key) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().ceilingKey(key);
      }
   }

   public NavigableSet<K> descendingKeySet() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.descendingKeySet == nullptr
            ? (this.descendingKeySet = Synchronized.navigableSet(this.delegate().descendingKeySet(), this.mutex))
            : this.descendingKeySet;
      }
   }

   public NavigableMap<K, V> descendingMap() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.descendingMap == nullptr ? (this.descendingMap = Synchronized.navigableMap(this.delegate().descendingMap(), this.mutex)) : this.descendingMap;
      }
   }

   public Entry<K, V> firstEntry() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return Synchronized.access$700(this.delegate().firstEntry(), this.mutex);
      }
   }

   public Entry<K, V> floorEntry(K key) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return Synchronized.access$700(this.delegate().floorEntry(key), this.mutex);
      }
   }

    K floorKey(K key) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().floorKey(key);
      }
   }

   public NavigableMap<K, V> headMap(K toKey, boolean inclusive) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return Synchronized.navigableMap(this.delegate().headMap(toKey, inclusive), this.mutex);
      }
   }

   public Entry<K, V> higherEntry(K key) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return Synchronized.access$700(this.delegate().higherEntry(key), this.mutex);
      }
   }

    K higherKey(K key) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().higherKey(key);
      }
   }

   public Entry<K, V> lastEntry() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return Synchronized.access$700(this.delegate().lastEntry(), this.mutex);
      }
   }

   public Entry<K, V> lowerEntry(K key) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return Synchronized.access$700(this.delegate().lowerEntry(key), this.mutex);
      }
   }

    K lowerKey(K key) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().lowerKey(key);
      }
   }

   public Set<K> keySet() {
      return this.navigableKeySet();
   }

   public NavigableSet<K> navigableKeySet() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.navigableKeySet == nullptr
            ? (this.navigableKeySet = Synchronized.navigableSet(this.delegate().navigableKeySet(), this.mutex))
            : this.navigableKeySet;
      }
   }

   public Entry<K, V> pollFirstEntry() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return Synchronized.access$700(this.delegate().pollFirstEntry(), this.mutex);
      }
   }

   public Entry<K, V> pollLastEntry() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return Synchronized.access$700(this.delegate().pollLastEntry(), this.mutex);
      }
   }

   public NavigableMap<K, V> subMap(K fromKey, boolean fromInclusive, K toKey, boolean toInclusive) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return Synchronized.navigableMap(this.delegate().subMap(fromKey, fromInclusive, toKey, toInclusive), this.mutex);
      }
   }

   public NavigableMap<K, V> tailMap(K fromKey, boolean inclusive) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return Synchronized.navigableMap(this.delegate().tailMap(fromKey, inclusive), this.mutex);
      }
   }

   public SortedMap<K, V> headMap(K toKey) {
      return this.headMap(toKey, false);
   }

   public SortedMap<K, V> subMap(K fromKey, K toKey) {
      return this.subMap(fromKey, true, toKey, false);
   }

   public SortedMap<K, V> tailMap(K fromKey) {
      return this.tailMap(fromKey, true);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
