#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TLongCollection.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableLongCollection/1.h"
#include "gnu/trove/iterator/TLongIterator.h"
#include "gnu/trove/procedure/TLongProcedure.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableLongCollection {
public:
    static const long serialVersionUID = 1820017752578914078L;
    const TLongCollection c;

    public TUnmodifiableLongCollection(TLongCollection c) {
      if (c == nullptr) {
         throw std::make_unique<NullPointerException>();
      } else {
         this.c = c;
      }
   }

    int size() {
      return this.c.size();
   }

    bool isEmpty() {
      return this.c.empty();
   }

    bool contains(long o) {
      return this.c.contains(o);
   }

   public long[] toArray() {
      return this.c.toArray();
   }

   public long[] toArray(long[] a) {
      return this.c.toArray(a);
   }

    std::string toString() {
      return this.c;
   }

    long getNoEntryValue() {
      return this.c.getNoEntryValue();
   }

    bool forEach(TLongProcedure procedure) {
      return this.c.forEach(procedure);
   }

    TLongIterator iterator() {
      return std::make_shared<1>(this);
   }

    bool add(long e) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool remove(long o) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool containsAll(Collection<?> coll) {
      return this.c.containsAll(coll);
   }

    bool containsAll(TLongCollection coll) {
      return this.c.containsAll(coll);
   }

    bool containsAll(long[] array) {
      return this.c.containsAll(array);
   }

    bool addAll(TLongCollection coll) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool addAll(Collection<? extends) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool addAll(long[] array) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool removeAll(Collection<?> coll) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool removeAll(TLongCollection coll) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool removeAll(long[] array) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainAll(Collection<?> coll) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainAll(TLongCollection coll) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainAll(long[] array) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void clear() {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace unmodifiable
} // namespace impl
} // namespace trove
} // namespace gnu
