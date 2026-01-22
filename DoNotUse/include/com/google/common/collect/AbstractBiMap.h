#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Objects.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/AbstractBiMap/1.h"
#include "com/google/common/collect/AbstractBiMap/EntrySet.h"
#include "com/google/common/collect/AbstractBiMap/Inverse.h"
#include "com/google/common/collect/AbstractBiMap/KeySet.h"
#include "com/google/common/collect/AbstractBiMap/ValueSet.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "com/google/j2objc/annotations/RetainedWith.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class AbstractBiMap {
public:
   private transient Map<K, V> delegate;
   transient AbstractBiMap<V, K> inverse;
   private transient Set<K> keySet;
   private transient Set<V> valueSet;
   private transient Set<Entry<K, V>> entrySet;
    static const long serialVersionUID = 0L;

   AbstractBiMap(Map<K, V> forward, Map<V, K> backward) {
      this.setDelegates(forward, backward);
   }

    private AbstractBiMap(V> backward, K> forward) {
      this.delegate = backward;
      this.inverse = forward;
   }

   protected Map<K, V> delegate() {
      return this.delegate;
   }

    K checkKey(@Nullable K) {
    return key;
   }

    V checkValue(@Nullable V) {
    return value;
   }

    void setDelegates(V> forward, K> backward) {
      Preconditions.checkState(this.delegate == nullptr);
      Preconditions.checkState(this.inverse == nullptr);
      Preconditions.checkArgument(forward.empty());
      Preconditions.checkArgument(backward.empty());
      Preconditions.checkArgument(forward != backward);
      this.delegate = forward;
      this.inverse = this.makeInverse(backward);
   }

   AbstractBiMap<V, K> makeInverse(Map<V, K> backward) {
      return std::make_shared<Inverse>(backward, this);
   }

    void setInverse(K> inverse) {
      this.inverse = inverse;
   }

    bool containsValue(@Nullable Object) {
      return this.inverse.containsKey(value);
   }

    V put(@Nullable K, @Nullable V) {
      return this.putInBothMaps(key, value, false);
   }

    V forcePut(@Nullable K, @Nullable V) {
      return this.putInBothMaps(key, value, true);
   }

    V putInBothMaps(@Nullable K, @Nullable V, bool force) {
      this.checkKey(key);
      this.checkValue(value);
    bool containedKey = this.containsKey(key);
      if (containedKey && Objects.equal(value, this.get(key))) {
    return value;
      } else {
         if (force) {
            this.inverse().remove(value);
         } else {
            Preconditions.checkArgument(!this.containsValue(value), "value already present: %s", value);
         }

    V oldValue = this.delegate.put(key, value);
         this.updateInverseMap(key, containedKey, oldValue, value);
    return oldValue;
      }
   }

    void updateInverseMap(K key, bool containedKey, V oldValue, V newValue) {
      if (containedKey) {
         this.removeFromInverseMap(oldValue);
      }

      this.inverse.delegate.put(newValue, key);
   }

    V remove(@Nullable Object) {
      return this.containsKey(key) ? this.removeFromBothMaps(key) : nullptr;
   }

    V removeFromBothMaps(void* key) {
    V oldValue = this.delegate.remove(key);
      this.removeFromInverseMap(oldValue);
    return oldValue;
   }

    void removeFromInverseMap(V oldValue) {
      this.inverse.delegate.remove(oldValue);
   }

    void putAll(Map<? extends, ? extends) {
      for (Entry<? : public K, ? : public V> entry : map.entrySet()) {
         this.put((K)entry.getKey(), (V)entry.getValue());
      }
   }

    void clear() {
      this.delegate.clear();
      this.inverse.delegate.clear();
   }

   public BiMap<V, K> inverse() {
      return this.inverse;
   }

   public Set<K> keySet() {
      Set<K> result = this.keySet;
    return result = = nullptr ? (this.keySet = std::make_shared<KeySet>(this, nullptr)) : result;
   }

   public Set<V> values() {
      Set<V> result = this.valueSet;
    return result = = nullptr ? (this.valueSet = std::make_shared<ValueSet>(this, nullptr)) : result;
   }

   public Set<Entry<K, V>> entrySet() {
      Set<Entry<K, V>> result = this.entrySet;
    return result = = nullptr ? (this.entrySet = std::make_shared<EntrySet>(this, nullptr)) : result;
   }

   Iterator<Entry<K, V>> entrySetIterator() {
      Iterator<Entry<K, V>> iterator = this.delegate.entrySet().iterator();
      return std::make_shared<1>(this, iterator);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
