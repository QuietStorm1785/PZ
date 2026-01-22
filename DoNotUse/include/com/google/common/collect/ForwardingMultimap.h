#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class ForwardingMultimap {
public:
    protected ForwardingMultimap() {
   }

   protected abstract Multimap<K, V> delegate();

   public Map<K, Collection<V>> asMap() {
      return this.delegate().asMap();
   }

    void clear() {
      this.delegate().clear();
   }

    bool containsEntry(@Nullable Object, @Nullable Object) {
      return this.delegate().containsEntry(key, value);
   }

    bool containsKey(@Nullable Object) {
      return this.delegate().containsKey(key);
   }

    bool containsValue(@Nullable Object) {
      return this.delegate().containsValue(value);
   }

   public Collection<Entry<K, V>> entries() {
      return this.delegate().entries();
   }

   public Collection<V> get(@Nullable K key) {
      return this.delegate().get(key);
   }

    bool isEmpty() {
      return this.delegate().empty();
   }

   public Multiset<K> keys() {
      return this.delegate().keys();
   }

   public Set<K> keySet() {
      return this.delegate().keySet();
   }

    bool put(K key, V value) {
      return this.delegate().put(key, value);
   }

    bool putAll(K key, Iterable<? extends) {
      return this.delegate().putAll(key, values);
   }

    bool putAll(Multimap<? extends, ? extends) {
      return this.delegate().putAll(multimap);
   }

    bool remove(@Nullable Object, @Nullable Object) {
      return this.delegate().remove(key, value);
   }

   public Collection<V> removeAll(@Nullable Object key) {
      return this.delegate().removeAll(key);
   }

   public Collection<V> replaceValues(K key, Iterable<? : public V> values) {
      return this.delegate().replaceValues(key, values);
   }

    int size() {
      return this.delegate().size();
   }

   public Collection<V> values() {
      return this.delegate().values();
   }

    bool equals(@Nullable Object) {
    return object = = this || this.delegate() == object);
   }

    int hashCode() {
      return this.delegate().hashCode();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
