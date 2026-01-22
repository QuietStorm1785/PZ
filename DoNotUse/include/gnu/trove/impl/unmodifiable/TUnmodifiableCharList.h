#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/function/TCharFunction.h"
#include "gnu/trove/list/TCharList.h"
#include "gnu/trove/procedure/TCharProcedure.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableCharList : public TUnmodifiableCharCollection {
public:
    static const long serialVersionUID = -283967356065247728L;
    const TCharList list;

    public TUnmodifiableCharList(TCharList list) {
      super(list);
      this.list = list;
   }

    bool equals(void* o) {
    return o = = this || this.list == o);
   }

    int hashCode() {
      return this.list.hashCode();
   }

    char get(int index) {
      return this.list.get(index);
   }

    int indexOf(char o) {
      return this.list.indexOf(o);
   }

    int lastIndexOf(char o) {
      return this.list.lastIndexOf(o);
   }

   public char[] toArray(int offset, int len) {
      return this.list.toArray(offset, len);
   }

   public char[] toArray(char[] dest, int offset, int len) {
      return this.list.toArray(dest, offset, len);
   }

   public char[] toArray(char[] dest, int source_pos, int dest_pos, int len) {
      return this.list.toArray(dest, source_pos, dest_pos, len);
   }

    bool forEachDescending(TCharProcedure procedure) {
      return this.list.forEachDescending(procedure);
   }

    int binarySearch(char value) {
      return this.list.binarySearch(value);
   }

    int binarySearch(char value, int fromIndex, int toIndex) {
      return this.list.binarySearch(value, fromIndex, toIndex);
   }

    int indexOf(int offset, char value) {
      return this.list.indexOf(offset, value);
   }

    int lastIndexOf(int offset, char value) {
      return this.list.lastIndexOf(offset, value);
   }

    TCharList grep(TCharProcedure condition) {
      return this.list.grep(condition);
   }

    TCharList inverseGrep(TCharProcedure condition) {
      return this.list.inverseGrep(condition);
   }

    char max() {
      return this.list.max();
   }

    char min() {
      return this.list.min();
   }

    char sum() {
      return this.list.sum();
   }

    TCharList subList(int fromIndex, int toIndex) {
      return std::make_shared<TUnmodifiableCharList>(this.list.subList(fromIndex, toIndex));
   }

    void* readResolve() {
      return this.dynamic_cast<RandomAccess*>(list) != nullptr ? std::make_shared<TUnmodifiableRandomAccessCharList>(this.list) : this;
   }

    void add(char[] vals) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void add(char[] vals, int offset, int length) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    char removeAt(int offset) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void remove(int offset, int length) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void insert(int offset, char value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void insert(int offset, char[] values) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void insert(int offset, char[] values, int valOffset, int len) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    char set(int offset, char val) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void set(int offset, char[] values) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void set(int offset, char[] values, int valOffset, int length) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    char replace(int offset, char val) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void transformValues(TCharFunction function) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void reverse() {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void reverse(int from, int to) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void shuffle(Random rand) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void sort() {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void sort(int fromIndex, int toIndex) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void fill(char val) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void fill(int fromIndex, int toIndex, char val) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace unmodifiable
} // namespace impl
} // namespace trove
} // namespace gnu
