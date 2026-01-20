#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/function/TIntFunction.h"
#include "gnu/trove/list/TIntList.h"
#include "gnu/trove/procedure/TIntProcedure.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableIntList : public TUnmodifiableIntCollection {
public:
    static const long serialVersionUID = -283967356065247728L;
    const TIntList list;

    public TUnmodifiableIntList(TIntList list) {
      super(list);
      this.list = list;
   }

    bool equals(void* o) {
    return o = = this || this.list == o);
   }

    int hashCode() {
      return this.list.hashCode();
   }

    int get(int index) {
      return this.list.get(index);
   }

    int indexOf(int o) {
      return this.list.indexOf(o);
   }

    int lastIndexOf(int o) {
      return this.list.lastIndexOf(o);
   }

   public int[] toArray(int offset, int len) {
      return this.list.toArray(offset, len);
   }

   public int[] toArray(int[] dest, int offset, int len) {
      return this.list.toArray(dest, offset, len);
   }

   public int[] toArray(int[] dest, int source_pos, int dest_pos, int len) {
      return this.list.toArray(dest, source_pos, dest_pos, len);
   }

    bool forEachDescending(TIntProcedure procedure) {
      return this.list.forEachDescending(procedure);
   }

    int binarySearch(int value) {
      return this.list.binarySearch(value);
   }

    int binarySearch(int value, int fromIndex, int toIndex) {
      return this.list.binarySearch(value, fromIndex, toIndex);
   }

    int indexOf(int offset, int value) {
      return this.list.indexOf(offset, value);
   }

    int lastIndexOf(int offset, int value) {
      return this.list.lastIndexOf(offset, value);
   }

    TIntList grep(TIntProcedure condition) {
      return this.list.grep(condition);
   }

    TIntList inverseGrep(TIntProcedure condition) {
      return this.list.inverseGrep(condition);
   }

    int max() {
      return this.list.max();
   }

    int min() {
      return this.list.min();
   }

    int sum() {
      return this.list.sum();
   }

    TIntList subList(int fromIndex, int toIndex) {
      return std::make_shared<TUnmodifiableIntList>(this.list.subList(fromIndex, toIndex));
   }

    void* readResolve() {
      return this.dynamic_cast<RandomAccess*>(list) != nullptr ? std::make_shared<TUnmodifiableRandomAccessIntList>(this.list) : this;
   }

    void add(int[] vals) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void add(int[] vals, int offset, int length) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    int removeAt(int offset) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void remove(int offset, int length) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void insert(int offset, int value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void insert(int offset, int[] values) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void insert(int offset, int[] values, int valOffset, int len) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    int set(int offset, int val) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void set(int offset, int[] values) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void set(int offset, int[] values, int valOffset, int length) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    int replace(int offset, int val) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void transformValues(TIntFunction function) {
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

    void fill(int val) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void fill(int fromIndex, int toIndex, int val) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace unmodifiable
} // namespace impl
} // namespace trove
} // namespace gnu
