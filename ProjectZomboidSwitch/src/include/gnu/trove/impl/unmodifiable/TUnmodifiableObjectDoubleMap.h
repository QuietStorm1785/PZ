#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TCollections.h"
#include "gnu/trove/TDoubleCollection.h"
#include "gnu/trove/function/TDoubleFunction.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableObjectDoubleMap/1.h"
#include "gnu/trove/iterator/TObjectDoubleIterator.h"
#include "gnu/trove/map/TObjectDoubleMap.h"
#include "gnu/trove/procedure/TDoubleProcedure.h"
#include "gnu/trove/procedure/TObjectDoubleProcedure.h"
#include "gnu/trove/procedure/TObjectProcedure.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableObjectDoubleMap {
public:
    static const long serialVersionUID = -1034234728574286014L;
   private const TObjectDoubleMap<K> m;
   private transient Set<K> keySet = nullptr;
   private transient TDoubleCollection values = nullptr;

    public TUnmodifiableObjectDoubleMap(TObjectDoubleMap<K> m) {
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

    bool containsValue(double val) {
      return this.m.containsValue(val);
   }

    double get(void* key) {
      return this.m.get(key);
   }

    double put(K key, double value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    double remove(void* key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(TObjectDoubleMap<? extends) {
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

    TDoubleCollection valueCollection() {
      if (this.values == nullptr) {
         this.values = TCollections.unmodifiableCollection(this.m.valueCollection());
      }

      return this.values;
   }

   public double[] values() {
      return this.m.values();
   }

   public double[] values(double[] array) {
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

    double getNoEntryValue() {
      return this.m.getNoEntryValue();
   }

    bool forEachKey(TObjectProcedure<? super) {
      return this.m.forEachKey(procedure);
   }

    bool forEachValue(TDoubleProcedure procedure) {
      return this.m.forEachValue(procedure);
   }

    bool forEachEntry(TObjectDoubleProcedure<? super) {
      return this.m.forEachEntry(procedure);
   }

   public TObjectDoubleIterator<K> iterator() {
      return std::make_shared<1>(this);
   }

    double putIfAbsent(K key, double value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void transformValues(TDoubleFunction function) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainEntries(TObjectDoubleProcedure<? super) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool increment(K key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool adjustValue(K key, double amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    double adjustOrPutValue(K key, double adjust_amount, double put_amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace unmodifiable
} // namespace impl
} // namespace trove
} // namespace gnu
