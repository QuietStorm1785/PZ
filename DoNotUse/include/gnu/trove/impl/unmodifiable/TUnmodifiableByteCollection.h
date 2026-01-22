#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TByteCollection.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableByteCollection/1.h"
#include "gnu/trove/iterator/TByteIterator.h"
#include "gnu/trove/procedure/TByteProcedure.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableByteCollection {
public:
    static const long serialVersionUID = 1820017752578914078L;
    const TByteCollection c;

    public TUnmodifiableByteCollection(TByteCollection c) {
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

    bool contains(uint8_t o) {
      return this.c.contains(o);
   }

   public byte[] toArray() {
      return this.c.toArray();
   }

   public byte[] toArray(byte[] a) {
      return this.c.toArray(a);
   }

    std::string toString() {
      return this.c;
   }

    uint8_t getNoEntryValue() {
      return this.c.getNoEntryValue();
   }

    bool forEach(TByteProcedure procedure) {
      return this.c.forEach(procedure);
   }

    TByteIterator iterator() {
      return std::make_shared<1>(this);
   }

    bool add(uint8_t e) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool remove(uint8_t o) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool containsAll(Collection<?> coll) {
      return this.c.containsAll(coll);
   }

    bool containsAll(TByteCollection coll) {
      return this.c.containsAll(coll);
   }

    bool containsAll(byte[] array) {
      return this.c.containsAll(array);
   }

    bool addAll(TByteCollection coll) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool addAll(Collection<? extends) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool addAll(byte[] array) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool removeAll(Collection<?> coll) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool removeAll(TByteCollection coll) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool removeAll(byte[] array) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainAll(Collection<?> coll) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainAll(TByteCollection coll) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainAll(byte[] array) {
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
