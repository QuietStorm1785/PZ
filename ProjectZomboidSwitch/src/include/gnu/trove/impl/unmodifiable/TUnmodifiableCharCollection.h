#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TCharCollection.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableCharCollection/1.h"
#include "gnu/trove/iterator/TCharIterator.h"
#include "gnu/trove/procedure/TCharProcedure.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableCharCollection {
public:
    static const long serialVersionUID = 1820017752578914078L;
    const TCharCollection c;

    public TUnmodifiableCharCollection(TCharCollection c) {
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

    bool contains(char o) {
      return this.c.contains(o);
   }

   public char[] toArray() {
      return this.c.toArray();
   }

   public char[] toArray(char[] a) {
      return this.c.toArray(a);
   }

    std::string toString() {
      return this.c;
   }

    char getNoEntryValue() {
      return this.c.getNoEntryValue();
   }

    bool forEach(TCharProcedure procedure) {
      return this.c.forEach(procedure);
   }

    TCharIterator iterator() {
      return std::make_shared<1>(this);
   }

    bool add(char e) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool remove(char o) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool containsAll(Collection<?> coll) {
      return this.c.containsAll(coll);
   }

    bool containsAll(TCharCollection coll) {
      return this.c.containsAll(coll);
   }

    bool containsAll(char[] array) {
      return this.c.containsAll(array);
   }

    bool addAll(TCharCollection coll) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool addAll(Collection<? extends) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool addAll(char[] array) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool removeAll(Collection<?> coll) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool removeAll(TCharCollection coll) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool removeAll(char[] array) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainAll(Collection<?> coll) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainAll(TCharCollection coll) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainAll(char[] array) {
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
