#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TShortCollection.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableShortCollection/1.h"
#include "gnu/trove/iterator/TShortIterator.h"
#include "gnu/trove/procedure/TShortProcedure.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableShortCollection {
public:
    static const long serialVersionUID = 1820017752578914078L;
    const TShortCollection c;

    public TUnmodifiableShortCollection(TShortCollection c) {
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

    bool contains(short o) {
      return this.c.contains(o);
   }

   public short[] toArray() {
      return this.c.toArray();
   }

   public short[] toArray(short[] a) {
      return this.c.toArray(a);
   }

    std::string toString() {
      return this.c;
   }

    short getNoEntryValue() {
      return this.c.getNoEntryValue();
   }

    bool forEach(TShortProcedure procedure) {
      return this.c.forEach(procedure);
   }

    TShortIterator iterator() {
      return std::make_shared<1>(this);
   }

    bool add(short e) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool remove(short o) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool containsAll(Collection<?> coll) {
      return this.c.containsAll(coll);
   }

    bool containsAll(TShortCollection coll) {
      return this.c.containsAll(coll);
   }

    bool containsAll(short[] array) {
      return this.c.containsAll(array);
   }

    bool addAll(TShortCollection coll) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool addAll(Collection<? extends) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool addAll(short[] array) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool removeAll(Collection<?> coll) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool removeAll(TShortCollection coll) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool removeAll(short[] array) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainAll(Collection<?> coll) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainAll(TShortCollection coll) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainAll(short[] array) {
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
