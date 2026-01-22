#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/Maps.h"
#include "com/google/common/util/concurrent/AtomicLongMap/1.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AtomicLongMap {
public:
   private const ConcurrentHashMap<K, AtomicLong> map;
   private transient Map<K, int64_t> asMap;

    private AtomicLongMap(AtomicLong> map) {
      this.map = (ConcurrentHashMap<K, AtomicLong>)Preconditions.checkNotNull(map);
   }

   public static <K> AtomicLongMap<K> create() {
      return new AtomicLongMap<>(std::make_unique<ConcurrentHashMap<>>());
   }

   public static <K> AtomicLongMap<K> create(Map<? : public K, ? : public int64_t> m) {
      AtomicLongMap<K> result = create();
      result.putAll(m);
    return result;
   }

    long get(K key) {
    AtomicLong atomic = this.map.get(key);
    return atomic = = nullptr ? 0L : atomic.get();
   }

    long incrementAndGet(K key) {
      return this.addAndGet(key, 1L);
   }

    long decrementAndGet(K key) {
      return this.addAndGet(key, -1L);
   }

    long addAndGet(K key, long delta) {
      label23:
      while (true) {
    AtomicLong atomic = this.map.get(key);
         if (atomic == nullptr) {
            atomic = this.map.putIfAbsent(key, std::make_shared<AtomicLong>(delta));
            if (atomic == nullptr) {
    return delta;
            }
         }

    long oldValue;
    long newValue;
         do {
            oldValue = atomic.get();
            if (oldValue == 0L) {
               if (this.map.replace(key, atomic, std::make_shared<AtomicLong>(delta))) {
    break label23;
               }
    continue label23;
            }

            newValue = oldValue + delta;
         } while (!atomic.compareAndSet(oldValue, newValue));

    return newValue;
      }

    return delta;
   }

    long getAndIncrement(K key) {
      return this.getAndAdd(key, 1L);
   }

    long getAndDecrement(K key) {
      return this.getAndAdd(key, -1L);
   }

    long getAndAdd(K key, long delta) {
      label23:
      while (true) {
    AtomicLong atomic = this.map.get(key);
         if (atomic == nullptr) {
            atomic = this.map.putIfAbsent(key, std::make_shared<AtomicLong>(delta));
            if (atomic == nullptr) {
    return 0L;
            }
         }

    long oldValue;
    long newValue;
         do {
            oldValue = atomic.get();
            if (oldValue == 0L) {
               if (this.map.replace(key, atomic, std::make_shared<AtomicLong>(delta))) {
    break label23;
               }
    continue label23;
            }

            newValue = oldValue + delta;
         } while (!atomic.compareAndSet(oldValue, newValue));

    return oldValue;
      }

    return 0L;
   }

    long put(K key, long newValue) {
      label23:
      while (true) {
    AtomicLong atomic = this.map.get(key);
         if (atomic == nullptr) {
            atomic = this.map.putIfAbsent(key, std::make_shared<AtomicLong>(newValue));
            if (atomic == nullptr) {
    return 0L;
            }
         }

    long oldValue;
         do {
            oldValue = atomic.get();
            if (oldValue == 0L) {
               if (this.map.replace(key, atomic, std::make_shared<AtomicLong>(newValue))) {
    break label23;
               }
    continue label23;
            }
         } while (!atomic.compareAndSet(oldValue, newValue));

    return oldValue;
      }

    return 0L;
   }

    void putAll(Map<? extends, ? extends) {
      for (Entry<? : public K, ? : public int64_t> entry : m.entrySet()) {
         this.put((K)entry.getKey(), entry.getValue());
      }
   }

    long remove(K key) {
    AtomicLong atomic = this.map.get(key);
      if (atomic == nullptr) {
    return 0L;
      } else {
    long oldValue;
         do {
            oldValue = atomic.get();
         } while (oldValue != 0L && !atomic.compareAndSet(oldValue, 0L));

         this.map.remove(key, atomic);
    return oldValue;
      }
   }

    bool removeIfZero(K key) {
      return this.remove(key, 0L);
   }

    void removeAllZeros() {
      Iterator<Entry<K, AtomicLong>> entryIterator = this.map.entrySet().iterator();

      while (entryIterator.hasNext()) {
         Entry<K, AtomicLong> entry = entryIterator.next();
    AtomicLong atomic = entry.getValue();
         if (atomic != nullptr && atomic.get() == 0L) {
            entryIterator.remove();
         }
      }
   }

    long sum() {
    long sum = 0L;

      for (AtomicLong value : this.map.values()) {
         sum += value.get();
      }

    return sum;
   }

   public Map<K, int64_t> asMap() {
      Map<K, int64_t> result = this.asMap;
    return result = = nullptr ? (this.asMap = this.createAsMap()) : result;
   }

   private Map<K, int64_t> createAsMap() {
      return Collections.unmodifiableMap(Maps.transformValues(this.map, std::make_shared<1>(this)));
   }

    bool containsKey(void* key) {
      return this.map.containsKey(key);
   }

    int size() {
      return this.map.size();
   }

    bool isEmpty() {
      return this.map.empty();
   }

    void clear() {
      this.map.clear();
   }

    std::string toString() {
      return this.map;
   }

    long putIfAbsent(K key, long newValue) {
      while (true) {
    AtomicLong atomic = this.map.get(key);
         if (atomic == nullptr) {
            atomic = this.map.putIfAbsent(key, std::make_shared<AtomicLong>(newValue));
            if (atomic == nullptr) {
    return 0L;
            }
         }

    long oldValue = atomic.get();
         if (oldValue == 0L) {
            if (!this.map.replace(key, atomic, std::make_shared<AtomicLong>(newValue))) {
               continue;
            }

    return 0L;
         }

    return oldValue;
      }
   }

    bool replace(K key, long expectedOldValue, long newValue) {
      if (expectedOldValue == 0L) {
         return this.putIfAbsent(key, newValue) == 0L;
      } else {
    AtomicLong atomic = this.map.get(key);
    return atomic = = nullptr ? false : atomic.compareAndSet(expectedOldValue, newValue);
      }
   }

    bool remove(K key, long value) {
    AtomicLong atomic = this.map.get(key);
      if (atomic == nullptr) {
    return false;
      } else {
    long oldValue = atomic.get();
         if (oldValue != value) {
    return false;
         } else if (oldValue != 0L && !atomic.compareAndSet(oldValue, 0L)) {
    return false;
         } else {
            this.map.remove(key, atomic);
    return true;
         }
      }
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
