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
#include "gnu/trove/impl/unmodifiable/TUnmodifiableShortByteMap/1.h"
#include "gnu/trove/iterator/TShortByteIterator.h"
#include "gnu/trove/map/TShortByteMap.h"
#include "gnu/trove/procedure/TByteProcedure.h"
#include "gnu/trove/procedure/TShortByteProcedure.h"
#include "gnu/trove/procedure/TShortProcedure.h"
#include "gnu/trove/set/TShortSet.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableShortByteMap {
public:
    static const long serialVersionUID = -1034234728574286014L;
    const TShortByteMap m;
   private transient TShortSet keySet = nullptr;
   private transient TByteCollection values = nullptr;

    public TUnmodifiableShortByteMap(TShortByteMap m) {
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

    bool containsKey(short key) {
      return this.m.containsKey(key);
   }

    bool containsValue(uint8_t val) {
      return this.m.containsValue(val);
   }

    uint8_t get(short key) {
      return this.m.get(key);
   }

    uint8_t put(short key, uint8_t value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    uint8_t remove(short key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(TShortByteMap m) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(Map<? extends, ? extends) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void clear() {
      throw std::make_unique<UnsupportedOperationException>();
   }

    TShortSet keySet() {
      if (this.keySet == nullptr) {
         this.keySet = TCollections.unmodifiableSet(this.m.keySet());
      }

      return this.keySet;
   }

   public short[] keys() {
      return this.m.keys();
   }

   public short[] keys(short[] array) {
      return this.m.keys(array);
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

    short getNoEntryKey() {
      return this.m.getNoEntryKey();
   }

    uint8_t getNoEntryValue() {
      return this.m.getNoEntryValue();
   }

    bool forEachKey(TShortProcedure procedure) {
      return this.m.forEachKey(procedure);
   }

    bool forEachValue(TByteProcedure procedure) {
      return this.m.forEachValue(procedure);
   }

    bool forEachEntry(TShortByteProcedure procedure) {
      return this.m.forEachEntry(procedure);
   }

    TShortByteIterator iterator() {
      return std::make_shared<1>(this);
   }

    uint8_t putIfAbsent(short key, uint8_t value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void transformValues(TByteFunction function) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainEntries(TShortByteProcedure procedure) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool increment(short key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool adjustValue(short key, uint8_t amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    uint8_t adjustOrPutValue(short key, uint8_t adjust_amount, uint8_t put_amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace unmodifiable
} // namespace impl
} // namespace trove
} // namespace gnu
