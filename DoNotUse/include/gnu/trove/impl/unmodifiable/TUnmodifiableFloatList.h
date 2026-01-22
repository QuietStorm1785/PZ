#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/function/TFloatFunction.h"
#include "gnu/trove/list/TFloatList.h"
#include "gnu/trove/procedure/TFloatProcedure.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableFloatList : public TUnmodifiableFloatCollection {
public:
    static const long serialVersionUID = -283967356065247728L;
    const TFloatList list;

    public TUnmodifiableFloatList(TFloatList list) {
      super(list);
      this.list = list;
   }

    bool equals(void* o) {
    return o = = this || this.list == o);
   }

    int hashCode() {
      return this.list.hashCode();
   }

    float get(int index) {
      return this.list.get(index);
   }

    int indexOf(float o) {
      return this.list.indexOf(o);
   }

    int lastIndexOf(float o) {
      return this.list.lastIndexOf(o);
   }

   public float[] toArray(int offset, int len) {
      return this.list.toArray(offset, len);
   }

   public float[] toArray(float[] dest, int offset, int len) {
      return this.list.toArray(dest, offset, len);
   }

   public float[] toArray(float[] dest, int source_pos, int dest_pos, int len) {
      return this.list.toArray(dest, source_pos, dest_pos, len);
   }

    bool forEachDescending(TFloatProcedure procedure) {
      return this.list.forEachDescending(procedure);
   }

    int binarySearch(float value) {
      return this.list.binarySearch(value);
   }

    int binarySearch(float value, int fromIndex, int toIndex) {
      return this.list.binarySearch(value, fromIndex, toIndex);
   }

    int indexOf(int offset, float value) {
      return this.list.indexOf(offset, value);
   }

    int lastIndexOf(int offset, float value) {
      return this.list.lastIndexOf(offset, value);
   }

    TFloatList grep(TFloatProcedure condition) {
      return this.list.grep(condition);
   }

    TFloatList inverseGrep(TFloatProcedure condition) {
      return this.list.inverseGrep(condition);
   }

    float max() {
      return this.list.max();
   }

    float min() {
      return this.list.min();
   }

    float sum() {
      return this.list.sum();
   }

    TFloatList subList(int fromIndex, int toIndex) {
      return std::make_shared<TUnmodifiableFloatList>(this.list.subList(fromIndex, toIndex));
   }

    void* readResolve() {
      return this.dynamic_cast<RandomAccess*>(list) != nullptr ? std::make_shared<TUnmodifiableRandomAccessFloatList>(this.list) : this;
   }

    void add(float[] vals) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void add(float[] vals, int offset, int length) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    float removeAt(int offset) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void remove(int offset, int length) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void insert(int offset, float value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void insert(int offset, float[] values) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void insert(int offset, float[] values, int valOffset, int len) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    float set(int offset, float val) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void set(int offset, float[] values) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void set(int offset, float[] values, int valOffset, int length) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    float replace(int offset, float val) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void transformValues(TFloatFunction function) {
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

    void fill(float val) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void fill(int fromIndex, int toIndex, float val) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace unmodifiable
} // namespace impl
} // namespace trove
} // namespace gnu
