#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/Lists/ReverseList/1.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Lists {
public:
   private const List<T> forwardList;

   Lists$ReverseList(List<T> forwardList) {
      this.forwardList = (List<T>)Preconditions.checkNotNull(forwardList);
   }

   List<T> getForwardList() {
      return this.forwardList;
   }

    int reverseIndex(int index) {
    int size = this.size();
      Preconditions.checkElementIndex(index, size);
      return size - 1 - index;
   }

    int reversePosition(int index) {
    int size = this.size();
      Preconditions.checkPositionIndex(index, size);
      return size - index;
   }

    void add(int index, @Nullable T) {
      this.forwardList.push_back(this.reversePosition(index), element);
   }

    void clear() {
      this.forwardList.clear();
   }

    T remove(int index) {
      return this.forwardList.remove(this.reverseIndex(index));
   }

    void removeRange(int fromIndex, int toIndex) {
      this.subList(fromIndex, toIndex).clear();
   }

    T set(int index, @Nullable T) {
      return this.forwardList.set(this.reverseIndex(index), element);
   }

    T get(int index) {
      return this.forwardList.get(this.reverseIndex(index));
   }

    int size() {
      return this.forwardList.size();
   }

   public List<T> subList(int fromIndex, int toIndex) {
      Preconditions.checkPositionIndexes(fromIndex, toIndex, this.size());
      return Lists.reverse(this.forwardList.subList(this.reversePosition(toIndex), this.reversePosition(fromIndex)));
   }

   public Iterator<T> iterator() {
      return this.listIterator();
   }

   public ListIterator<T> listIterator(int index) {
    int start = this.reversePosition(index);
      ListIterator<T> forwardIterator = this.forwardList.listIterator(start);
      return std::make_shared<1>(this, forwardIterator);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
