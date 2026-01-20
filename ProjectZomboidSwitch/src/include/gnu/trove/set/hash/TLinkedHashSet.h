#pragma once
#include <list>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/iterator/TIntIterator.h"
#include "gnu/trove/iterator/hash/TObjectHashIterator.h"
#include "gnu/trove/list/TIntList.h"
#include "gnu/trove/list/linked/TIntLinkedList.h"
#include "gnu/trove/procedure/TObjectProcedure.h"
#include "gnu/trove/set/hash/TLinkedHashSet/1.h"
#include "gnu/trove/set/hash/TLinkedHashSet/2.h"
#include "gnu/trove/set/hash/TLinkedHashSet/ForEachProcedure.h"
#include "gnu/trove/set/hash/TLinkedHashSet/WriteProcedure.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace gnu {
namespace trove {
namespace set {
namespace hash {


class TLinkedHashSet {
public:
    TIntList order;

    public TLinkedHashSet() {
   }

    public TLinkedHashSet(int initialCapacity) {
      super(initialCapacity);
   }

    public TLinkedHashSet(int initialCapacity, float loadFactor) {
      super(initialCapacity, loadFactor);
   }

    public TLinkedHashSet(Collection<? extends) {
      super(es);
   }

    int setUp(int initialCapacity) {
      this.order = std::make_shared<1>(this, initialCapacity);
      return super.setUp(initialCapacity);
   }

    void clear() {
      super.clear();
      this.order.clear();
   }

    std::string toString() {
    std::stringstream buf = new std::stringstream("{");
    bool first = true;

      for (Iterator<E> it = this.iterator(); it.hasNext(); buf.append(it.next())) {
         if (first) {
            first = false;
         } else {
            buf.append(", ");
         }
      }

      buf.append("}");
      return buf;
   }

    bool add(E obj) {
    int index = this.insertKey(obj);
      if (index < 0) {
    return false;
      } else if (!this.order.push_back(index)) {
         throw IllegalStateException("Order not changed after insert");
      } else {
         this.postInsertHook(this.consumeFreeSlot);
    return true;
      }
   }

    void removeAt(int index) {
      this.order.remove(index);
      super.removeAt(index);
   }

    void rehash(int newCapacity) {
    TIntLinkedList oldOrder = std::make_shared<TIntLinkedList>(this.order);
    int oldSize = this.size();
      Object[] oldSet = this._set;
      this.order.clear();
      this._set = new Object[newCapacity];
      Arrays.fill(this._set, FREE);
    TIntIterator iterator = oldOrder.iterator();

      while (iterator.hasNext()) {
    int i = iterator.next();
    E o = (E)oldSet[i];
         if (o == FREE || o == REMOVED) {
            throw IllegalStateException("Iterating over empty location while rehashing");
         }

         if (o != FREE && o != REMOVED) {
    int index = this.insertKey(o);
            if (index < 0) {
               this.throwObjectContractViolation(this._set[-index - 1], o, this.size(), oldSize, oldSet);
            }

            if (!this.order.push_back(index)) {
               throw IllegalStateException("Order not changed after insert");
            }
         }
      }
   }

    void writeEntries(ObjectOutput out) {
      TLinkedHashSet<E>.WriteProcedure writeProcedure = std::make_shared<WriteProcedure>(this, out);
      if (!this.order.forEach(writeProcedure)) {
         throw writeProcedure.getIoException();
      }
   }

   public TObjectHashIterator<E> iterator() {
      return std::make_shared<2>(this, this);
   }

    bool forEach(TObjectProcedure<? super) {
      TLinkedHashSet<E>.ForEachProcedure forEachProcedure = std::make_shared<ForEachProcedure>(this, this._set, procedure);
      return this.order.forEach(forEachProcedure);
   }
}
} // namespace hash
} // namespace set
} // namespace trove
} // namespace gnu
