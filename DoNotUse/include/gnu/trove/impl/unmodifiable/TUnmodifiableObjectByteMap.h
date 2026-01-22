#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TByteCollection.h"
#include "gnu/trove/TCollections.h"
#include "gnu/trove/function/TByteFunction.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableObjectByteMap/1.h"
#include "gnu/trove/iterator/TObjectByteIterator.h"
#include "gnu/trove/map/TObjectByteMap.h"
#include "gnu/trove/procedure/TByteProcedure.h"
#include "gnu/trove/procedure/TObjectByteProcedure.h"
#include "gnu/trove/procedure/TObjectProcedure.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableObjectByteMap {
public:
    static const long serialVersionUID = -1034234728574286014L;
   private const TObjectByteMap<K> m;
   private transient Set<K> keySet = nullptr;
   private transient TByteCollection values = nullptr;

    public TUnmodifiableObjectByteMap(TObjectByteMap<K> m) {
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

    bool containsValue(uint8_t val) {
      return this.m.containsValue(val);
   }

    uint8_t get(void* key) {
      return this.m.get(key);
   }

    uint8_t put(K key, uint8_t value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    uint8_t remove(void* key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(TObjectByteMap<? extends) {
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

    TByteCollection valueCollection() {
      if (this.values == nullptr) {
         this.values = TCollections.unmodifiableCollection(this.m.valueCollection());
      }

      return this.values;
   }

   public byte[] values() {
      return this.m.values();
   }

   public byte[] values(byte[] array) {
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

    uint8_t getNoEntryValue() {
      return this.m.getNoEntryValue();
   }

    bool forEachKey(TObjectProcedure<? super) {
      return this.m.forEachKey(procedure);
   }

    bool forEachValue(TByteProcedure procedure) {
      return this.m.forEachValue(procedure);
   }

    bool forEachEntry(TObjectByteProcedure<? super) {
      return this.m.forEachEntry(procedure);
   }

   public TObjectByteIterator<K> iterator() {
      return std::make_shared<1>(this);
   }

    uint8_t putIfAbsent(K key, uint8_t value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void transformValues(TByteFunction function) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainEntries(TObjectByteProcedure<? super) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool increment(K key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool adjustValue(K key, uint8_t amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    uint8_t adjustOrPutValue(K key, uint8_t adjust_amount, uint8_t put_amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace unmodifiable
} // namespace impl
} // namespace trove
} // namespace gnu
