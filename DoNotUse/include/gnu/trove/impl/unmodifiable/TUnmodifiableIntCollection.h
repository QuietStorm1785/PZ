#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TIntCollection.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableIntCollection/1.h"
#include "gnu/trove/iterator/TIntIterator.h"
#include "gnu/trove/procedure/TIntProcedure.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableIntCollection {
public:
    static const long serialVersionUID = 1820017752578914078L;
    const TIntCollection c;

    public TUnmodifiableIntCollection(TIntCollection c) {
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

    bool contains(int o) {
      return this.c.contains(o);
   }

   public int[] toArray() {
      return this.c.toArray();
   }

   public int[] toArray(int[] a) {
      return this.c.toArray(a);
   }

    std::string toString() {
      return this.c;
   }

    int getNoEntryValue() {
      return this.c.getNoEntryValue();
   }

    bool forEach(TIntProcedure procedure) {
      return this.c.forEach(procedure);
   }

    TIntIterator iterator() {
      return std::make_shared<1>(this);
   }

    bool add(int e) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool remove(int o) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool containsAll(Collection<?> coll) {
      return this.c.containsAll(coll);
   }

    bool containsAll(TIntCollection coll) {
      return this.c.containsAll(coll);
   }

    bool containsAll(int[] array) {
      return this.c.containsAll(array);
   }

    bool addAll(TIntCollection coll) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool addAll(Collection<? extends) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool addAll(int[] array) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool removeAll(Collection<?> coll) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool removeAll(TIntCollection coll) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool removeAll(int[] array) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainAll(Collection<?> coll) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainAll(TIntCollection coll) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainAll(int[] array) {
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
