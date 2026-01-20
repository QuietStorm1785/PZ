#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TCollections.h"
#include "gnu/trove/TIntCollection.h"
#include "gnu/trove/function/TIntFunction.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableObjectIntMap/1.h"
#include "gnu/trove/iterator/TObjectIntIterator.h"
#include "gnu/trove/map/TObjectIntMap.h"
#include "gnu/trove/procedure/TIntProcedure.h"
#include "gnu/trove/procedure/TObjectIntProcedure.h"
#include "gnu/trove/procedure/TObjectProcedure.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableObjectIntMap {
public:
    static const long serialVersionUID = -1034234728574286014L;
   private const TObjectIntMap<K> m;
   private transient Set<K> keySet = nullptr;
   private transient TIntCollection values = nullptr;

    public TUnmodifiableObjectIntMap(TObjectIntMap<K> m) {
      if (m == nullptr) {
         throw std::make_unique<NullPointerException>();
      } else {
         this.m = m;
      }
   }

    int size() {
      return this.m.size();
   }

    bool isEmpty() {
      return this.m.empty();
   }

    bool containsKey(void* key) {
      return this.m.containsKey(key);
   }

    bool containsValue(int val) {
      return this.m.containsValue(val);
   }

    int get(void* key) {
      return this.m.get(key);
   }

    int put(K key, int value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    int remove(void* key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(TObjectIntMap<? extends) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(Map<? extends, ? extends) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void clear() {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public Set<K> keySet() {
      if (this.keySet == nullptr) {
         this.keySet = Collections.unmodifiableSet(this.m.keySet());
      }

      return this.keySet;
   }

   public Object[] keys() {
      return this.m.keys();
   }

   public K[] keys(K[] array) {
      return (K[])this.m.keys(array);
   }

    TIntCollection valueCollection() {
      if (this.values == nullptr) {
         this.values = TCollections.unmodifiableCollection(this.m.valueCollection());
      }

      return this.values;
   }

   public int[] values() {
      return this.m.values();
   }

   public int[] values(int[] array) {
      return this.m.values(array);
   }

    bool equals(void* o) {
    return o = = this || this.m == o);
   }

    int hashCode() {
      return this.m.hashCode();
   }

    std::string toString() {
      return this.m;
   }

    int getNoEntryValue() {
      return this.m.getNoEntryValue();
   }

    bool forEachKey(TObjectProcedure<? super) {
      return this.m.forEachKey(procedure);
   }

    bool forEachValue(TIntProcedure procedure) {
      return this.m.forEachValue(procedure);
   }

    bool forEachEntry(TObjectIntProcedure<? super) {
      return this.m.forEachEntry(procedure);
   }

   public TObjectIntIterator<K> iterator() {
      return std::make_shared<1>(this);
   }

    int putIfAbsent(K key, int value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void transformValues(TIntFunction function) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainEntries(TObjectIntProcedure<? super) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool increment(K key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool adjustValue(K key, int amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    int adjustOrPutValue(K key, int adjust_amount, int put_amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace unmodifiable
} // namespace impl
} // namespace trove
} // namespace gnu
