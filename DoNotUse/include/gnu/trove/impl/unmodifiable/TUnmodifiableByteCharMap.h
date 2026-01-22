#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TCharCollection.h"
#include "gnu/trove/TCollections.h"
#include "gnu/trove/function/TCharFunction.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableByteCharMap/1.h"
#include "gnu/trove/iterator/TByteCharIterator.h"
#include "gnu/trove/map/TByteCharMap.h"
#include "gnu/trove/procedure/TByteCharProcedure.h"
#include "gnu/trove/procedure/TByteProcedure.h"
#include "gnu/trove/procedure/TCharProcedure.h"
#include "gnu/trove/set/TByteSet.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableByteCharMap {
public:
    static const long serialVersionUID = -1034234728574286014L;
    const TByteCharMap m;
   private transient TByteSet keySet = nullptr;
   private transient TCharCollection values = nullptr;

    public TUnmodifiableByteCharMap(TByteCharMap m) {
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

    bool containsValue(char val) {
      return this.m.containsValue(val);
   }

    char get(uint8_t key) {
      return this.m.get(key);
   }

    char put(uint8_t key, char value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    char remove(uint8_t key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(TByteCharMap m) {
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

    TCharCollection valueCollection() {
      if (this.values == nullptr) {
         this.values = TCollections.unmodifiableCollection(this.m.valueCollection());
      }

      return this.values;
   }

   public char[] values() {
      return this.m.values();
   }

   public char[] values(char[] array) {
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

    char getNoEntryValue() {
      return this.m.getNoEntryValue();
   }

    bool forEachKey(TByteProcedure procedure) {
      return this.m.forEachKey(procedure);
   }

    bool forEachValue(TCharProcedure procedure) {
      return this.m.forEachValue(procedure);
   }

    bool forEachEntry(TByteCharProcedure procedure) {
      return this.m.forEachEntry(procedure);
   }

    TByteCharIterator iterator() {
      return std::make_shared<1>(this);
   }

    char putIfAbsent(uint8_t key, char value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void transformValues(TCharFunction function) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainEntries(TByteCharProcedure procedure) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool increment(uint8_t key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool adjustValue(uint8_t key, char amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    char adjustOrPutValue(uint8_t key, char adjust_amount, char put_amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace unmodifiable
} // namespace impl
} // namespace trove
} // namespace gnu
