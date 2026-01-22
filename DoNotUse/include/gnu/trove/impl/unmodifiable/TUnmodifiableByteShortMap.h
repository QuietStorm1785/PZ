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
#include "gnu/trove/impl/unmodifiable/TUnmodifiableByteShortMap/1.h"
#include "gnu/trove/iterator/TByteShortIterator.h"
#include "gnu/trove/map/TByteShortMap.h"
#include "gnu/trove/procedure/TByteProcedure.h"
#include "gnu/trove/procedure/TByteShortProcedure.h"
#include "gnu/trove/procedure/TShortProcedure.h"
#include "gnu/trove/set/TByteSet.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableByteShortMap {
public:
    static const long serialVersionUID = -1034234728574286014L;
    const TByteShortMap m;
   private transient TByteSet keySet = nullptr;
   private transient TShortCollection values = nullptr;

    public TUnmodifiableByteShortMap(TByteShortMap m) {
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

    bool containsValue(short val) {
      return this.m.containsValue(val);
   }

    short get(uint8_t key) {
      return this.m.get(key);
   }

    short put(uint8_t key, short value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    short remove(uint8_t key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(TByteShortMap m) {
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

    uint8_t getNoEntryKey() {
      return this.m.getNoEntryKey();
   }

    short getNoEntryValue() {
      return this.m.getNoEntryValue();
   }

    bool forEachKey(TByteProcedure procedure) {
      return this.m.forEachKey(procedure);
   }

    bool forEachValue(TShortProcedure procedure) {
      return this.m.forEachValue(procedure);
   }

    bool forEachEntry(TByteShortProcedure procedure) {
      return this.m.forEachEntry(procedure);
   }

    TByteShortIterator iterator() {
      return std::make_shared<1>(this);
   }

    short putIfAbsent(uint8_t key, short value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void transformValues(TShortFunction function) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainEntries(TByteShortProcedure procedure) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool increment(uint8_t key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool adjustValue(uint8_t key, short amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    short adjustOrPutValue(uint8_t key, short adjust_amount, short put_amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace unmodifiable
} // namespace impl
} // namespace trove
} // namespace gnu
