#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TCollections.h"
#include "gnu/trove/TLongCollection.h"
#include "gnu/trove/function/TLongFunction.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableByteLongMap/1.h"
#include "gnu/trove/iterator/TByteLongIterator.h"
#include "gnu/trove/map/TByteLongMap.h"
#include "gnu/trove/procedure/TByteLongProcedure.h"
#include "gnu/trove/procedure/TByteProcedure.h"
#include "gnu/trove/procedure/TLongProcedure.h"
#include "gnu/trove/set/TByteSet.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableByteLongMap {
public:
    static const long serialVersionUID = -1034234728574286014L;
    const TByteLongMap m;
   private transient TByteSet keySet = nullptr;
   private transient TLongCollection values = nullptr;

    public TUnmodifiableByteLongMap(TByteLongMap m) {
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

    bool containsKey(uint8_t key) {
      return this.m.containsKey(key);
   }

    bool containsValue(long val) {
      return this.m.containsValue(val);
   }

    long get(uint8_t key) {
      return this.m.get(key);
   }

    long put(uint8_t key, long value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    long remove(uint8_t key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(TByteLongMap m) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(Map<? extends, ? extends) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void clear() {
      throw std::make_unique<UnsupportedOperationException>();
   }

    TByteSet keySet() {
      if (this.keySet == nullptr) {
         this.keySet = TCollections.unmodifiableSet(this.m.keySet());
      }

      return this.keySet;
   }

   public byte[] keys() {
      return this.m.keys();
   }

   public byte[] keys(byte[] array) {
      return this.m.keys(array);
   }

    TLongCollection valueCollection() {
      if (this.values == nullptr) {
         this.values = TCollections.unmodifiableCollection(this.m.valueCollection());
      }

      return this.values;
   }

   public long[] values() {
      return this.m.values();
   }

   public long[] values(long[] array) {
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

    uint8_t getNoEntryKey() {
      return this.m.getNoEntryKey();
   }

    long getNoEntryValue() {
      return this.m.getNoEntryValue();
   }

    bool forEachKey(TByteProcedure procedure) {
      return this.m.forEachKey(procedure);
   }

    bool forEachValue(TLongProcedure procedure) {
      return this.m.forEachValue(procedure);
   }

    bool forEachEntry(TByteLongProcedure procedure) {
      return this.m.forEachEntry(procedure);
   }

    TByteLongIterator iterator() {
      return std::make_shared<1>(this);
   }

    long putIfAbsent(uint8_t key, long value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void transformValues(TLongFunction function) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainEntries(TByteLongProcedure procedure) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool increment(uint8_t key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool adjustValue(uint8_t key, long amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    long adjustOrPutValue(uint8_t key, long adjust_amount, long put_amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace unmodifiable
} // namespace impl
} // namespace trove
} // namespace gnu
