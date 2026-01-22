#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/function/TByteFunction.h"
#include "gnu/trove/list/TByteList.h"
#include "gnu/trove/procedure/TByteProcedure.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableByteList : public TUnmodifiableByteCollection {
public:
    static const long serialVersionUID = -283967356065247728L;
    const TByteList list;

    public TUnmodifiableByteList(TByteList list) {
      super(list);
      this.list = list;
   }

    bool equals(void* o) {
    return o = = this || this.list == o);
   }

    int hashCode() {
      return this.list.hashCode();
   }

    uint8_t get(int index) {
      return this.list.get(index);
   }

    int indexOf(uint8_t o) {
      return this.list.indexOf(o);
   }

    int lastIndexOf(uint8_t o) {
      return this.list.lastIndexOf(o);
   }

   public byte[] toArray(int offset, int len) {
      return this.list.toArray(offset, len);
   }

   public byte[] toArray(byte[] dest, int offset, int len) {
      return this.list.toArray(dest, offset, len);
   }

   public byte[] toArray(byte[] dest, int source_pos, int dest_pos, int len) {
      return this.list.toArray(dest, source_pos, dest_pos, len);
   }

    bool forEachDescending(TByteProcedure procedure) {
      return this.list.forEachDescending(procedure);
   }

    int binarySearch(uint8_t value) {
      return this.list.binarySearch(value);
   }

    int binarySearch(uint8_t value, int fromIndex, int toIndex) {
      return this.list.binarySearch(value, fromIndex, toIndex);
   }

    int indexOf(int offset, uint8_t value) {
      return this.list.indexOf(offset, value);
   }

    int lastIndexOf(int offset, uint8_t value) {
      return this.list.lastIndexOf(offset, value);
   }

    TByteList grep(TByteProcedure condition) {
      return this.list.grep(condition);
   }

    TByteList inverseGrep(TByteProcedure condition) {
      return this.list.inverseGrep(condition);
   }

    uint8_t max() {
      return this.list.max();
   }

    uint8_t min() {
      return this.list.min();
   }

    uint8_t sum() {
      return this.list.sum();
   }

    TByteList subList(int fromIndex, int toIndex) {
      return std::make_shared<TUnmodifiableByteList>(this.list.subList(fromIndex, toIndex));
   }

    void* readResolve() {
      return this.dynamic_cast<RandomAccess*>(list) != nullptr ? std::make_shared<TUnmodifiableRandomAccessByteList>(this.list) : this;
   }

    void add(byte[] vals) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void add(byte[] vals, int offset, int length) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    uint8_t removeAt(int offset) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void remove(int offset, int length) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void insert(int offset, uint8_t value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void insert(int offset, byte[] values) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void insert(int offset, byte[] values, int valOffset, int len) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    uint8_t set(int offset, uint8_t val) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void set(int offset, byte[] values) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void set(int offset, byte[] values, int valOffset, int length) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    uint8_t replace(int offset, uint8_t val) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void transformValues(TByteFunction function) {
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

    void fill(uint8_t val) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void fill(int fromIndex, int toIndex, uint8_t val) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace unmodifiable
} // namespace impl
} // namespace trove
} // namespace gnu
