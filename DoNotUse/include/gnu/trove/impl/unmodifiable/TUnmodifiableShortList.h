#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/function/TShortFunction.h"
#include "gnu/trove/list/TShortList.h"
#include "gnu/trove/procedure/TShortProcedure.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableShortList : public TUnmodifiableShortCollection {
public:
    static const long serialVersionUID = -283967356065247728L;
    const TShortList list;

    public TUnmodifiableShortList(TShortList list) {
      super(list);
      this.list = list;
   }

    bool equals(void* o) {
    return o = = this || this.list == o);
   }

    int hashCode() {
      return this.list.hashCode();
   }

    short get(int index) {
      return this.list.get(index);
   }

    int indexOf(short o) {
      return this.list.indexOf(o);
   }

    int lastIndexOf(short o) {
      return this.list.lastIndexOf(o);
   }

   public short[] toArray(int offset, int len) {
      return this.list.toArray(offset, len);
   }

   public short[] toArray(short[] dest, int offset, int len) {
      return this.list.toArray(dest, offset, len);
   }

   public short[] toArray(short[] dest, int source_pos, int dest_pos, int len) {
      return this.list.toArray(dest, source_pos, dest_pos, len);
   }

    bool forEachDescending(TShortProcedure procedure) {
      return this.list.forEachDescending(procedure);
   }

    int binarySearch(short value) {
      return this.list.binarySearch(value);
   }

    int binarySearch(short value, int fromIndex, int toIndex) {
      return this.list.binarySearch(value, fromIndex, toIndex);
   }

    int indexOf(int offset, short value) {
      return this.list.indexOf(offset, value);
   }

    int lastIndexOf(int offset, short value) {
      return this.list.lastIndexOf(offset, value);
   }

    TShortList grep(TShortProcedure condition) {
      return this.list.grep(condition);
   }

    TShortList inverseGrep(TShortProcedure condition) {
      return this.list.inverseGrep(condition);
   }

    short max() {
      return this.list.max();
   }

    short min() {
      return this.list.min();
   }

    short sum() {
      return this.list.sum();
   }

    TShortList subList(int fromIndex, int toIndex) {
      return std::make_shared<TUnmodifiableShortList>(this.list.subList(fromIndex, toIndex));
   }

    void* readResolve() {
      return this.dynamic_cast<RandomAccess*>(list) != nullptr ? std::make_shared<TUnmodifiableRandomAccessShortList>(this.list) : this;
   }

    void add(short[] vals) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void add(short[] vals, int offset, int length) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    short removeAt(int offset) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void remove(int offset, int length) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void insert(int offset, short value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void insert(int offset, short[] values) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void insert(int offset, short[] values, int valOffset, int len) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    short set(int offset, short val) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void set(int offset, short[] values) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void set(int offset, short[] values, int valOffset, int length) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    short replace(int offset, short val) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void transformValues(TShortFunction function) {
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

    void fill(short val) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void fill(int fromIndex, int toIndex, short val) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace unmodifiable
} // namespace impl
} // namespace trove
} // namespace gnu
