#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/function/TDoubleFunction.h"
#include "gnu/trove/list/TDoubleList.h"
#include "gnu/trove/procedure/TDoubleProcedure.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableDoubleList : public TUnmodifiableDoubleCollection {
public:
    static const long serialVersionUID = -283967356065247728L;
    const TDoubleList list;

    public TUnmodifiableDoubleList(TDoubleList list) {
      super(list);
      this.list = list;
   }

    bool equals(void* o) {
    return o = = this || this.list == o);
   }

    int hashCode() {
      return this.list.hashCode();
   }

    double get(int index) {
      return this.list.get(index);
   }

    int indexOf(double o) {
      return this.list.indexOf(o);
   }

    int lastIndexOf(double o) {
      return this.list.lastIndexOf(o);
   }

   public double[] toArray(int offset, int len) {
      return this.list.toArray(offset, len);
   }

   public double[] toArray(double[] dest, int offset, int len) {
      return this.list.toArray(dest, offset, len);
   }

   public double[] toArray(double[] dest, int source_pos, int dest_pos, int len) {
      return this.list.toArray(dest, source_pos, dest_pos, len);
   }

    bool forEachDescending(TDoubleProcedure procedure) {
      return this.list.forEachDescending(procedure);
   }

    int binarySearch(double value) {
      return this.list.binarySearch(value);
   }

    int binarySearch(double value, int fromIndex, int toIndex) {
      return this.list.binarySearch(value, fromIndex, toIndex);
   }

    int indexOf(int offset, double value) {
      return this.list.indexOf(offset, value);
   }

    int lastIndexOf(int offset, double value) {
      return this.list.lastIndexOf(offset, value);
   }

    TDoubleList grep(TDoubleProcedure condition) {
      return this.list.grep(condition);
   }

    TDoubleList inverseGrep(TDoubleProcedure condition) {
      return this.list.inverseGrep(condition);
   }

    double max() {
      return this.list.max();
   }

    double min() {
      return this.list.min();
   }

    double sum() {
      return this.list.sum();
   }

    TDoubleList subList(int fromIndex, int toIndex) {
      return std::make_shared<TUnmodifiableDoubleList>(this.list.subList(fromIndex, toIndex));
   }

    void* readResolve() {
      return this.dynamic_cast<RandomAccess*>(list) != nullptr ? std::make_shared<TUnmodifiableRandomAccessDoubleList>(this.list) : this;
   }

    void add(double[] vals) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void add(double[] vals, int offset, int length) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    double removeAt(int offset) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void remove(int offset, int length) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void insert(int offset, double value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void insert(int offset, double[] values) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void insert(int offset, double[] values, int valOffset, int len) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    double set(int offset, double val) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void set(int offset, double[] values) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void set(int offset, double[] values, int valOffset, int length) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    double replace(int offset, double val) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void transformValues(TDoubleFunction function) {
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

    void fill(double val) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void fill(int fromIndex, int toIndex, double val) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace unmodifiable
} // namespace impl
} // namespace trove
} // namespace gnu
