#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Multiset/Entry.h"
#include <fstream>
#include <iostream>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Multisets {
public:
   const Multiset<? : public E> delegate;
   transient Set<E> elementSet;
   transient Set<Entry<E>> entrySet;
    static const long serialVersionUID = 0L;

   Multisets$UnmodifiableMultiset(Multiset<? : public E> delegate) {
      this.delegate = delegate;
   }

   protected Multiset<E> delegate() {
      return (Multiset<E>)this.delegate;
   }

   Set<E> createElementSet() {
      return Collections.unmodifiableSet(this.delegate.elementSet());
   }

   public Set<E> elementSet() {
      Set<E> es = this.elementSet;
    return es = = nullptr ? (this.elementSet = this.createElementSet()) : es;
   }

   public Set<Entry<E>> entrySet() {
      Set<Entry<E>> es = this.entrySet;
    return es = = nullptr ? (this.entrySet = Collections.unmodifiableSet(this.delegate.entrySet())) : es;
   }

   public Iterator<E> iterator() {
      return Iterators.unmodifiableIterator(this.delegate.iterator());
   }

    bool add(E element) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    int add(E element, int occurences) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool addAll(Collection<? extends) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool remove(void* element) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    int remove(void* element, int occurrences) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool removeAll(Collection<?> elementsToRemove) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainAll(Collection<?> elementsToRetain) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void clear() {
      throw std::make_unique<UnsupportedOperationException>();
   }

    int setCount(E element, int count) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool setCount(E element, int oldCount, int newCount) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
