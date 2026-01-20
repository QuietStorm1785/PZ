#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TCollections.h"
#include "gnu/trove/TShortCollection.h"
#include "gnu/trove/function/TShortFunction.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableObjectShortMap/1.h"
#include "gnu/trove/iterator/TObjectShortIterator.h"
#include "gnu/trove/map/TObjectShortMap.h"
#include "gnu/trove/procedure/TObjectProcedure.h"
#include "gnu/trove/procedure/TObjectShortProcedure.h"
#include "gnu/trove/procedure/TShortProcedure.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableObjectShortMap {
public:
    static const long serialVersionUID = -1034234728574286014L;
   private const TObjectShortMap<K> m;
   private transient Set<K> keySet = nullptr;
   private transient TShortCollection values = nullptr;

    public TUnmodifiableObjectShortMap(TObjectShortMap<K> m) {
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

    bool containsValue(short val) {
      return this.m.containsValue(val);
   }

    short get(void* key) {
      return this.m.get(key);
   }

    short put(K key, short value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    short remove(void* key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(TObjectShortMap<? extends) {
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

    TShortCollection valueCollection() {
      if (this.values == nullptr) {
         this.values = TCollections.unmodifiableCollection(this.m.valueCollection());
      }

      return this.values;
   }

   public short[] values() {
      return this.m.values();
   }

   public short[] values(short[] array) {
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

    short getNoEntryValue() {
      return this.m.getNoEntryValue();
   }

    bool forEachKey(TObjectProcedure<? super) {
      return this.m.forEachKey(procedure);
   }

    bool forEachValue(TShortProcedure procedure) {
      return this.m.forEachValue(procedure);
   }

    bool forEachEntry(TObjectShortProcedure<? super) {
      return this.m.forEachEntry(procedure);
   }

   public TObjectShortIterator<K> iterator() {
      return std::make_shared<1>(this);
   }

    short putIfAbsent(K key, short value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void transformValues(TShortFunction function) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainEntries(TObjectShortProcedure<? super) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool increment(K key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool adjustValue(K key, short amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    short adjustOrPutValue(K key, short adjust_amount, short put_amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace unmodifiable
} // namespace impl
} // namespace trove
} // namespace gnu
