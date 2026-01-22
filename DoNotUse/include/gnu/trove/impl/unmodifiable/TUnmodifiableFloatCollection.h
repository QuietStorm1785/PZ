#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TFloatCollection.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableFloatCollection/1.h"
#include "gnu/trove/iterator/TFloatIterator.h"
#include "gnu/trove/procedure/TFloatProcedure.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableFloatCollection {
public:
    static const long serialVersionUID = 1820017752578914078L;
    const TFloatCollection c;

    public TUnmodifiableFloatCollection(TFloatCollection c) {
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

    bool contains(float o) {
      return this.c.contains(o);
   }

   public float[] toArray() {
      return this.c.toArray();
   }

   public float[] toArray(float[] a) {
      return this.c.toArray(a);
   }

    std::string toString() {
      return this.c;
   }

    float getNoEntryValue() {
      return this.c.getNoEntryValue();
   }

    bool forEach(TFloatProcedure procedure) {
      return this.c.forEach(procedure);
   }

    TFloatIterator iterator() {
      return std::make_shared<1>(this);
   }

    bool add(float e) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool remove(float o) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool containsAll(Collection<?> coll) {
      return this.c.containsAll(coll);
   }

    bool containsAll(TFloatCollection coll) {
      return this.c.containsAll(coll);
   }

    bool containsAll(float[] array) {
      return this.c.containsAll(array);
   }

    bool addAll(TFloatCollection coll) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool addAll(Collection<? extends) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool addAll(float[] array) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool removeAll(Collection<?> coll) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool removeAll(TFloatCollection coll) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool removeAll(float[] array) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainAll(Collection<?> coll) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainAll(TFloatCollection coll) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainAll(float[] array) {
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
