#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Objects.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class ForwardingMap {
public:
    protected ForwardingMap() {
   }

   protected abstract Map<K, V> delegate();

    int size() {
      return this.delegate().size();
   }

    bool isEmpty() {
      return this.delegate().empty();
   }

    V remove(void* object) {
      return this.delegate().remove(object);
   }

    void clear() {
      this.delegate().clear();
   }

    bool containsKey(@Nullable Object) {
      return this.delegate().containsKey(key);
   }

    bool containsValue(@Nullable Object) {
      return this.delegate().containsValue(value);
   }

    V get(@Nullable Object) {
      return this.delegate().get(key);
   }

    V put(K key, V value) {
      return this.delegate().put(key, value);
   }

    void putAll(Map<? extends, ? extends) {
      this.delegate().putAll(map);
   }

   public Set<K> keySet() {
      return this.delegate().keySet();
   }

   public Collection<V> values() {
      return this.delegate().values();
   }

   public Set<Entry<K, V>> entrySet() {
      return this.delegate().entrySet();
   }

    bool equals(@Nullable Object) {
    return object = = this || this.delegate() == object);
   }

    int hashCode() {
      return this.delegate().hashCode();
   }

    void standardPutAll(Map<? extends, ? extends) {
      Maps.putAllImpl(this, map);
   }

    V standardRemove(@Nullable Object) {
      Iterator<Entry<K, V>> entryIterator = this.entrySet().iterator();

      while (entryIterator.hasNext()) {
         Entry<K, V> entry = entryIterator.next();
         if (Objects.equal(entry.getKey(), key)) {
    V value = entry.getValue();
            entryIterator.remove();
    return value;
         }
      }

    return nullptr;
   }

    void standardClear() {
      Iterators.clear(this.entrySet().iterator());
   }

    bool standardContainsKey(@Nullable Object) {
      return Maps.containsKeyImpl(this, key);
   }

    bool standardContainsValue(@Nullable Object) {
      return Maps.containsValueImpl(this, value);
   }

    bool standardIsEmpty() {
      return !this.entrySet().iterator().hasNext();
   }

    bool standardEquals(@Nullable Object) {
      return Maps.equalsImpl(this, object);
   }

    int standardHashCode() {
      return Sets.hashCodeImpl(this.entrySet());
   }

    std::string standardToString() {
      return Maps.toStringImpl(this);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
