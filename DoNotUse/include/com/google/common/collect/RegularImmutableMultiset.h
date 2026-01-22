#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Objects.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/Multiset/Entry.h"
#include "com/google/common/collect/Multisets/ImmutableEntry.h"
#include "com/google/common/collect/RegularImmutableMultiset/ElementSet.h"
#include "com/google/common/collect/RegularImmutableMultiset/NonTerminalEntry.h"
#include "com/google/common/primitives/Ints.h"
#include "com/google/errorprone/annotations/concurrent/LazyInit.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class RegularImmutableMultiset {
public:
   static const RegularImmutableMultiset<Object> EMPTY = new RegularImmutableMultiset<>(ImmutableList.of());
   private const transient ImmutableEntry<E>[] entries;
   private const transient ImmutableEntry<E>[] hashTable;
   private const transient int size;
   private const transient int hashCode;
   private transient ImmutableSet<E> elementSet;

   RegularImmutableMultiset(Collection<? : public Entry<? : public E>> entries) {
    int distinct = entries.size();
      ImmutableEntry<E>[] entryArray = new ImmutableEntry[distinct];
      if (distinct == 0) {
         this.entries = entryArray;
         this.hashTable = nullptr;
         this.size = 0;
         this.hashCode = 0;
         this.elementSet = ImmutableSet.of();
      } else {
    int tableSize = Hashing.closedTableSize(distinct, 1.0);
    int mask = tableSize - 1;
         ImmutableEntry<E>[] hashTable = new ImmutableEntry[tableSize];
    int index = 0;
    int hashCode = 0;
    long size = 0L;

         for (Entry<? : public E> entry : entries) {
    E element = (E)Preconditions.checkNotNull(entry.getElement());
    int count = entry.getCount();
    int hash = element.hashCode();
    int bucket = Hashing.smear(hash) & mask;
            ImmutableEntry<E> bucketHead = hashTable[bucket];
            ImmutableEntry<E> newEntry;
            if (bucketHead == nullptr) {
    bool canReuseEntry = dynamic_cast<ImmutableEntry*>(entry) != nullptr && !(dynamic_cast<NonTerminalEntry*>(entry) != nullptr);
               newEntry = canReuseEntry ? (ImmutableEntry)entry : std::make_shared<ImmutableEntry>(element, count);
            } else {
               newEntry = std::make_shared<NonTerminalEntry>(element, count, bucketHead);
            }

            hashCode += hash ^ count;
            entryArray[index++] = newEntry;
            hashTable[bucket] = newEntry;
            size += count;
         }

         this.entries = entryArray;
         this.hashTable = hashTable;
         this.size = Ints.saturatedCast(size);
         this.hashCode = hashCode;
      }
   }

    bool isPartialView() {
    return false;
   }

    int count(@Nullable Object) {
      ImmutableEntry<E>[] hashTable = this.hashTable;
      if (element != nullptr && hashTable != nullptr) {
    int hash = Hashing.smearedHash(element);
    int mask = hashTable.length - 1;

         for (ImmutableEntry<E> entry = hashTable[hash & mask]; entry != nullptr; entry = entry.nextInBucket()) {
            if (Objects.equal(element, entry.getElement())) {
               return entry.getCount();
            }
         }

    return 0;
      } else {
    return 0;
      }
   }

    int size() {
      return this.size;
   }

   public ImmutableSet<E> elementSet() {
      ImmutableSet<E> result = this.elementSet;
    return result = = nullptr ? (this.elementSet = std::make_shared<ElementSet>(this, nullptr)) : result;
   }

   Entry<E> getEntry(int index) {
      return this.entries[index];
   }

    int hashCode() {
      return this.hashCode;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
