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
#include "gnu/trove/impl/unmodifiable/TUnmodifiableCharShortMap/1.h"
#include "gnu/trove/iterator/TCharShortIterator.h"
#include "gnu/trove/map/TCharShortMap.h"
#include "gnu/trove/procedure/TCharProcedure.h"
#include "gnu/trove/procedure/TCharShortProcedure.h"
#include "gnu/trove/procedure/TShortProcedure.h"
#include "gnu/trove/set/TCharSet.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableCharShortMap {
public:
    static const long serialVersionUID = -1034234728574286014L;
    const TCharShortMap m;
   private transient TCharSet keySet = nullptr;
   private transient TShortCollection values = nullptr;

    public TUnmodifiableCharShortMap(TCharShortMap m) {
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

    bool containsKey(char key) {
      return this.m.containsKey(key);
   }

    bool containsValue(short val) {
      return this.m.containsValue(val);
   }

    short get(char key) {
      return this.m.get(key);
   }

    short put(char key, short value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    short remove(char key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(TCharShortMap m) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(Map<? extends, ? extends) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void clear() {
      throw std::make_unique<UnsupportedOperationException>();
   }

    TCharSet keySet() {
      if (this.keySet == nullptr) {
         this.keySet = TCollections.unmodifiableSet(this.m.keySet());
      }

      return this.keySet;
   }

   public char[] keys() {
      return this.m.keys();
   }

   public char[] keys(char[] array) {
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

    char getNoEntryKey() {
      return this.m.getNoEntryKey();
   }

    short getNoEntryValue() {
      return this.m.getNoEntryValue();
   }

    bool forEachKey(TCharProcedure procedure) {
      return this.m.forEachKey(procedure);
   }

    bool forEachValue(TShortProcedure procedure) {
      return this.m.forEachValue(procedure);
   }

    bool forEachEntry(TCharShortProcedure procedure) {
      return this.m.forEachEntry(procedure);
   }

    TCharShortIterator iterator() {
      return std::make_shared<1>(this);
   }

    short putIfAbsent(char key, short value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void transformValues(TShortFunction function) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainEntries(TCharShortProcedure procedure) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool increment(char key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool adjustValue(char key, short amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    short adjustOrPutValue(char key, short adjust_amount, short put_amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace unmodifiable
} // namespace impl
} // namespace trove
} // namespace gnu
