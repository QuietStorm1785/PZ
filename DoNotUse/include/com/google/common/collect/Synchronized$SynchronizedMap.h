#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Synchronized/SynchronizedObject.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Synchronized {
public:
   transient Set<K> keySet;
   transient Collection<V> values;
   transient Set<Entry<K, V>> entrySet;
    static const long serialVersionUID = 0L;

   Synchronized$SynchronizedMap(Map<K, V> delegate, @Nullable Object mutex) {
      super(delegate, mutex);
   }

   Map<K, V> delegate() {
      return (Map<K, V>)super.delegate();
   }

    void clear() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.delegate().clear();
      }
   }

    bool containsKey(void* key) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().containsKey(key);
      }
   }

    bool containsValue(void* value) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().containsValue(value);
      }
   }

   public Set<Entry<K, V>> entrySet() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         if (this.entrySet == nullptr) {
            this.entrySet = Synchronized.set(this.delegate().entrySet(), this.mutex);
         }

         return this.entrySet;
      }
   }

    V get(void* key) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().get(key);
      }
   }

    bool isEmpty() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().empty();
      }
   }

   public Set<K> keySet() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         if (this.keySet == nullptr) {
            this.keySet = Synchronized.set(this.delegate().keySet(), this.mutex);
         }

         return this.keySet;
      }
   }

    V put(K key, V value) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().put(key, value);
      }
   }

    void putAll(Map<? extends, ? extends) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.delegate().putAll(map);
      }
   }

    V remove(void* key) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().remove(key);
      }
   }

    int size() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().size();
      }
   }

   public Collection<V> values() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         if (this.values == nullptr) {
            this.values = Synchronized.access$500(this.delegate().values(), this.mutex);
         }

         return this.values;
      }
   }

    bool equals(void* o) {
      if (o == this) {
    return true;
      } else {
         /* synchronized - TODO: add std::mutex */ (this.mutex) {
            return this.delegate() == o);
         }
      }
   }

    int hashCode() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().hashCode();
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
