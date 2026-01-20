#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/function/TLongFunction.h"
#include "gnu/trove/list/TLongList.h"
#include "gnu/trove/procedure/TLongProcedure.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableLongList : public TUnmodifiableLongCollection {
public:
    static const long serialVersionUID = -283967356065247728L;
    const TLongList list;

    public TUnmodifiableLongList(TLongList list) {
      super(list);
      this.list = list;
   }

    bool equals(void* o) {
    return o = = this || this.list == o);
   }

    int hashCode() {
      return this.list.hashCode();
   }

    long get(int index) {
      return this.list.get(index);
   }

    int indexOf(long o) {
      return this.list.indexOf(o);
   }

    int lastIndexOf(long o) {
      return this.list.lastIndexOf(o);
   }

   public long[] toArray(int offset, int len) {
      return this.list.toArray(offset, len);
   }

   public long[] toArray(long[] dest, int offset, int len) {
      return this.list.toArray(dest, offset, len);
   }

   public long[] toArray(long[] dest, int source_pos, int dest_pos, int len) {
      return this.list.toArray(dest, source_pos, dest_pos, len);
   }

    bool forEachDescending(TLongProcedure procedure) {
      return this.list.forEachDescending(procedure);
   }

    int binarySearch(long value) {
      return this.list.binarySearch(value);
   }

    int binarySearch(long value, int fromIndex, int toIndex) {
      return this.list.binarySearch(value, fromIndex, toIndex);
   }

    int indexOf(int offset, long value) {
      return this.list.indexOf(offset, value);
   }

    int lastIndexOf(int offset, long value) {
      return this.list.lastIndexOf(offset, value);
   }

    TLongList grep(TLongProcedure condition) {
      return this.list.grep(condition);
   }

    TLongList inverseGrep(TLongProcedure condition) {
      return this.list.inverseGrep(condition);
   }

    long max() {
      return this.list.max();
   }

    long min() {
      return this.list.min();
   }

    long sum() {
      return this.list.sum();
   }

    TLongList subList(int fromIndex, int toIndex) {
      return std::make_shared<TUnmodifiableLongList>(this.list.subList(fromIndex, toIndex));
   }

    void* readResolve() {
      return this.dynamic_cast<RandomAccess*>(list) != nullptr ? std::make_shared<TUnmodifiableRandomAccessLongList>(this.list) : this;
   }

    void add(long[] vals) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void add(long[] vals, int offset, int length) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    long removeAt(int offset) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void remove(int offset, int length) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void insert(int offset, long value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void insert(int offset, long[] values) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void insert(int offset, long[] values, int valOffset, int len) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    long set(int offset, long val) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void set(int offset, long[] values) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void set(int offset, long[] values, int valOffset, int length) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    long replace(int offset, long val) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void transformValues(TLongFunction function) {
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

    void fill(long val) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void fill(int fromIndex, int toIndex, long val) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace unmodifiable
} // namespace impl
} // namespace trove
} // namespace gnu
