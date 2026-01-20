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
#include "gnu/trove/impl/unmodifiable/TUnmodifiableShortLongMap/1.h"
#include "gnu/trove/iterator/TShortLongIterator.h"
#include "gnu/trove/map/TShortLongMap.h"
#include "gnu/trove/procedure/TLongProcedure.h"
#include "gnu/trove/procedure/TShortLongProcedure.h"
#include "gnu/trove/procedure/TShortProcedure.h"
#include "gnu/trove/set/TShortSet.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableShortLongMap {
public:
    static const long serialVersionUID = -1034234728574286014L;
    const TShortLongMap m;
   private transient TShortSet keySet = nullptr;
   private transient TLongCollection values = nullptr;

    public TUnmodifiableShortLongMap(TShortLongMap m) {
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

    bool containsValue(long val) {
      return this.m.containsValue(val);
   }

    long get(short key) {
      return this.m.get(key);
   }

    long put(short key, long value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    long remove(short key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(TShortLongMap m) {
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

    short getNoEntryKey() {
      return this.m.getNoEntryKey();
   }

    long getNoEntryValue() {
      return this.m.getNoEntryValue();
   }

    bool forEachKey(TShortProcedure procedure) {
      return this.m.forEachKey(procedure);
   }

    bool forEachValue(TLongProcedure procedure) {
      return this.m.forEachValue(procedure);
   }

    bool forEachEntry(TShortLongProcedure procedure) {
      return this.m.forEachEntry(procedure);
   }

    TShortLongIterator iterator() {
      return std::make_shared<1>(this);
   }

    long putIfAbsent(short key, long value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void transformValues(TLongFunction function) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainEntries(TShortLongProcedure procedure) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool increment(short key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool adjustValue(short key, long amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    long adjustOrPutValue(short key, long adjust_amount, long put_amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace unmodifiable
} // namespace impl
} // namespace trove
} // namespace gnu
