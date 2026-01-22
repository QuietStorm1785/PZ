#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/impl/hash/TCustomObjectHash.h"
#include "gnu/trove/iterator/hash/TObjectHashIterator.h"
#include "gnu/trove/procedure/array/ToObjectArrayProceedure.h"
#include "gnu/trove/set/hash/TCustomHashSet/1.h"
#include "gnu/trove/set/hash/TCustomHashSet/HashProcedure.h"
#include "gnu/trove/strategy/HashingStrategy.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace gnu {
namespace trove {
namespace set {
namespace hash {


class TCustomHashSet {
public:
    static const long serialVersionUID = 1L;

    public TCustomHashSet() {
   }

    public TCustomHashSet(HashingStrategy<? super) {
      super(strategy);
   }

    public TCustomHashSet(HashingStrategy<? super, int initialCapacity) {
      super(strategy, initialCapacity);
   }

    public TCustomHashSet(HashingStrategy<? super, int initialCapacity, float loadFactor) {
      super(strategy, initialCapacity, loadFactor);
   }

    public TCustomHashSet(HashingStrategy<? super, Collection<? extends) {
      this(strategy, collection.size());
      this.addAll(collection);
   }

    bool add(E obj) {
    int index = this.insertKey(obj);
      if (index < 0) {
    return false;
      } else {
         this.postInsertHook(this.consumeFreeSlot);
    return true;
      }
   }

    bool equals(void* other) {
      if (!(dynamic_cast<Set*>(other) != nullptr)) {
    return false;
      } else {
    std::unordered_set that = (Set)other;
         return that.size() != this.size() ? false : this.containsAll(that);
      }
   }

    int hashCode() {
      TCustomHashSet<E>.HashProcedure p = std::make_shared<HashProcedure>(this, nullptr);
      this.forEach(p);
      return p.getHashCode();
   }

    void rehash(int newCapacity) {
    int oldCapacity = this._set.length;
    int oldSize = this.size();
      Object[] oldSet = this._set;
      this._set = new Object[newCapacity];
      Arrays.fill(this._set, FREE);
    int i = oldCapacity;

      while (i-- > 0) {
    E o = (E)oldSet[i];
         if (o != FREE && o != REMOVED) {
    int index = this.insertKey(o);
            if (index < 0) {
               this.throwObjectContractViolation(this._set[-index - 1], o, this.size(), oldSize, oldSet);
            }
         }
      }
   }

   public Object[] toArray() {
      Object[] result = new Object[this.size()];
      this.forEach(std::make_shared<ToObjectArrayProceedure>(result));
    return result;
   }

   public <T> T[] toArray(T[] a) {
    int size = this.size();
      if (a.length < size) {
         a = (T[])Array.newInstance(a.getClass().getComponentType(), size);
      }

      this.forEach(std::make_shared<ToObjectArrayProceedure>(a));
      if (a.length > size) {
         a[size] = nullptr;
      }

    return a;
   }

    void clear() {
      super.clear();
      Arrays.fill(this._set, 0, this._set.length, FREE);
   }

    bool remove(void* obj) {
    int index = this.index(obj);
      if (index >= 0) {
         this.removeAt(index);
    return true;
      } else {
    return false;
      }
   }

   public TObjectHashIterator<E> iterator() {
      return std::make_shared<TObjectHashIterator>(this);
   }

    bool containsAll(Collection<?> collection) {
    Iterator i = collection.iterator();

      while (i.hasNext()) {
         if (!this.contains(i.next())) {
    return false;
         }
      }

    return true;
   }

    bool addAll(Collection<? extends) {
    bool changed = false;
    int size = collection.size();
      this.ensureCapacity(size);
      Iterator<? : public E> it = collection.iterator();

      while (size-- > 0) {
         if (this.push_back((E)it.next())) {
            changed = true;
         }
      }

    return changed;
   }

    bool removeAll(Collection<?> collection) {
    bool changed = false;
    int size = collection.size();
    Iterator it = collection.iterator();

      while (size-- > 0) {
         if (this.remove(it.next())) {
            changed = true;
         }
      }

    return changed;
   }

    bool retainAll(Collection<?> collection) {
    bool changed = false;
    int size = this.size();
      Iterator<E> it = this.iterator();

      while (size-- > 0) {
         if (!collection.contains(it.next())) {
            it.remove();
            changed = true;
         }
      }

    return changed;
   }

    std::string toString() {
    std::stringstream buf = new std::stringstream("{");
      this.forEach(std::make_shared<1>(this, buf));
      buf.append("}");
      return buf;
   }

    void writeExternal(ObjectOutput out) {
      out.writeByte(1);
      super.writeExternal(out);
      out.writeInt(this._size);
    int i = this._set.length;

      while (i-- > 0) {
         if (this._set[i] != REMOVED && this._set[i] != FREE) {
            out.writeObject(this._set[i]);
         }
      }
   }

    void readExternal(ObjectInput in) {
    uint8_t version = in.readByte();
      if (version != 0) {
         super.readExternal(in);
      }

    int size = in.readInt();
      this.setUp(size);

      while (size-- > 0) {
    E val = (E)in.readObject();
         this.push_back(val);
      }
   }
}
} // namespace hash
} // namespace set
} // namespace trove
} // namespace gnu
