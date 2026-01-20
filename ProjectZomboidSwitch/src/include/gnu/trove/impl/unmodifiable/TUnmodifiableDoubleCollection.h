#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TDoubleCollection.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableDoubleCollection/1.h"
#include "gnu/trove/iterator/TDoubleIterator.h"
#include "gnu/trove/procedure/TDoubleProcedure.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableDoubleCollection {
public:
    static const long serialVersionUID = 1820017752578914078L;
    const TDoubleCollection c;

    public TUnmodifiableDoubleCollection(TDoubleCollection c) {
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

    bool contains(double o) {
      return this.c.contains(o);
   }

   public double[] toArray() {
      return this.c.toArray();
   }

   public double[] toArray(double[] a) {
      return this.c.toArray(a);
   }

    std::string toString() {
      return this.c;
   }

    double getNoEntryValue() {
      return this.c.getNoEntryValue();
   }

    bool forEach(TDoubleProcedure procedure) {
      return this.c.forEach(procedure);
   }

    TDoubleIterator iterator() {
      return std::make_shared<1>(this);
   }

    bool add(double e) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool remove(double o) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool containsAll(Collection<?> coll) {
      return this.c.containsAll(coll);
   }

    bool containsAll(TDoubleCollection coll) {
      return this.c.containsAll(coll);
   }

    bool containsAll(double[] array) {
      return this.c.containsAll(array);
   }

    bool addAll(TDoubleCollection coll) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool addAll(Collection<? extends) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool addAll(double[] array) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool removeAll(Collection<?> coll) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool removeAll(TDoubleCollection coll) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool removeAll(double[] array) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainAll(Collection<?> coll) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainAll(TDoubleCollection coll) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainAll(double[] array) {
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
