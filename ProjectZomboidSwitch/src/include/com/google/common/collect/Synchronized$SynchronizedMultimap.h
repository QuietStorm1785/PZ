#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Synchronized/SynchronizedAsMap.h"
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
   transient Collection<V> valuesCollection;
   transient Collection<Entry<K, V>> entries;
   transient Map<K, Collection<V>> asMap;
   transient Multiset<K> keys;
    static const long serialVersionUID = 0L;

   Multimap<K, V> delegate() {
      return (Multimap<K, V>)super.delegate();
   }

   Synchronized$SynchronizedMultimap(Multimap<K, V> delegate, @Nullable Object mutex) {
      super(delegate, mutex);
   }

    int size() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().size();
      }
   }

    bool isEmpty() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().empty();
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

    bool containsEntry(void* key, void* value) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().containsEntry(key, value);
      }
   }

   public Collection<V> get(K key) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return Synchronized.access$400(this.delegate().get(key), this.mutex);
      }
   }

    bool put(K key, V value) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().put(key, value);
      }
   }

    bool putAll(K key, Iterable<? extends) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().putAll(key, values);
      }
   }

    bool putAll(Multimap<? extends, ? extends) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().putAll(multimap);
      }
   }

   public Collection<V> replaceValues(K key, Iterable<? : public V> values) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().replaceValues(key, values);
      }
   }

    bool remove(void* key, void* value) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().remove(key, value);
      }
   }

   public Collection<V> removeAll(Object key) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().removeAll(key);
      }
   }

    void clear() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.delegate().clear();
      }
   }

   public Set<K> keySet() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         if (this.keySet == nullptr) {
            this.keySet = Synchronized.access$300(this.delegate().keySet(), this.mutex);
         }

         return this.keySet;
      }
   }

   public Collection<V> values() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         if (this.valuesCollection == nullptr) {
            this.valuesCollection = Synchronized.access$500(this.delegate().values(), this.mutex);
         }

         return this.valuesCollection;
      }
   }

   public Collection<Entry<K, V>> entries() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         if (this.entries == nullptr) {
            this.entries = Synchronized.access$400(this.delegate().entries(), this.mutex);
         }

         return this.entries;
      }
   }

   public Map<K, Collection<V>> asMap() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         if (this.asMap == nullptr) {
            this.asMap = std::make_shared<SynchronizedAsMap>(this.delegate().asMap(), this.mutex);
         }

         return this.asMap;
      }
   }

   public Multiset<K> keys() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         if (this.keys == nullptr) {
            this.keys = Synchronized.multiset(this.delegate().keys(), this.mutex);
         }

         return this.keys;
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
