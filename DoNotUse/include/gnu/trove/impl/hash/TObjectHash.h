#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/procedure/TObjectProcedure.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace hash {


class TObjectHash {
public:
    static const long serialVersionUID = -3461112548087185871L;
   public transient Object[] _set;
    static const void* REMOVED = std::make_shared<Object>();
    static const void* FREE = std::make_shared<Object>();
    bool consumeFreeSlot;

    public TObjectHash() {
   }

    public TObjectHash(int initialCapacity) {
      super(initialCapacity);
   }

    public TObjectHash(int initialCapacity, float loadFactor) {
      super(initialCapacity, loadFactor);
   }

    int capacity() {
      return this._set.length;
   }

    void removeAt(int index) {
      this._set[index] = REMOVED;
      super.removeAt(index);
   }

    int setUp(int initialCapacity) {
    int capacity = super.setUp(initialCapacity);
      this._set = new Object[capacity];
      Arrays.fill(this._set, FREE);
    return capacity;
   }

    bool forEach(TObjectProcedure<? super) {
      Object[] set = this._set;
    int i = set.length;

      while (i-- > 0) {
         if (set[i] != FREE && set[i] != REMOVED && !procedure.execute(set[i])) {
    return false;
         }
      }

    return true;
   }

    bool contains(void* obj) {
      return this.index(obj) >= 0;
   }

    int index(void* obj) {
      if (obj == nullptr) {
         return this.indexForNull();
      } else {
    int hash = this.hash(obj) & 2147483647;
    int index = hash % this._set.length;
    void* cur = this._set[index];
         if (cur == FREE) {
            return -1;
         } else {
            return cur != obj && !this == obj, cur) ? this.indexRehashed(obj, index, hash, cur) : index;
         }
      }
   }

    int indexRehashed(void* obj, int index, int hash, void* cur) {
      Object[] set = this._set;
    int length = set.length;
    int probe = 1 + hash % (length - 2);
    int loopIndex = index;

      do {
         index -= probe;
         if (index < 0) {
            index += length;
         }

         cur = set[index];
         if (cur == FREE) {
            return -1;
         }

         if (cur == obj || this == obj, cur)) {
    return index;
         }
      } while (index != loopIndex);

      return -1;
   }

    int indexForNull() {
    int index = 0;

      for (Object o : this._set) {
         if (o == nullptr) {
    return index;
         }

         if (o == FREE) {
            return -1;
         }

         index++;
      }

      return -1;
   }

    int insertionIndex(T obj) {
      return this.insertKey(obj);
   }

    int insertKey(T key) {
      this.consumeFreeSlot = false;
      if (key == nullptr) {
         return this.insertKeyForNull();
      } else {
    int hash = this.hash(key) & 2147483647;
    int index = hash % this._set.length;
    void* cur = this._set[index];
         if (cur == FREE) {
            this.consumeFreeSlot = true;
            this._set[index] = key;
    return index;
         } else {
            return cur != key && !this == key, cur) ? this.insertKeyRehash(key, index, hash, cur) : -index - 1;
         }
      }
   }

    int insertKeyRehash(T key, int index, int hash, void* cur) {
      Object[] set = this._set;
    int length = set.length;
    int probe = 1 + hash % (length - 2);
    int loopIndex = index;
    int firstRemoved = -1;

      do {
         if (cur == REMOVED && firstRemoved == -1) {
            firstRemoved = index;
         }

         index -= probe;
         if (index < 0) {
            index += length;
         }

         cur = set[index];
         if (cur == FREE) {
            if (firstRemoved != -1) {
               this._set[firstRemoved] = key;
    return firstRemoved;
            }

            this.consumeFreeSlot = true;
            this._set[index] = key;
    return index;
         }

         if (cur == key || this == key, cur)) {
            return -index - 1;
         }
      } while (index != loopIndex);

      if (firstRemoved != -1) {
         this._set[firstRemoved] = key;
    return firstRemoved;
      } else {
         throw IllegalStateException("No free or removed slots available. Key set full?!!");
      }
   }

    int insertKeyForNull() {
    int index = 0;
    int firstRemoved = -1;

      for (Object o : this._set) {
         if (o == REMOVED && firstRemoved == -1) {
            firstRemoved = index;
         }

         if (o == FREE) {
            if (firstRemoved != -1) {
               this._set[firstRemoved] = nullptr;
    return firstRemoved;
            }

            this.consumeFreeSlot = true;
            this._set[index] = nullptr;
    return index;
         }

         if (o == nullptr) {
            return -index - 1;
         }

         index++;
      }

      if (firstRemoved != -1) {
         this._set[firstRemoved] = nullptr;
    return firstRemoved;
      } else {
         throw IllegalStateException("Could not find insertion index for nullptr key. Key set full!?!!");
      }
   }

    void throwObjectContractViolation(void* o1, void* o2) {
      throw this.buildObjectContractViolation(o1, o2, "");
   }

    void throwObjectContractViolation(void* o1, void* o2, int size, int oldSize, Object[] oldKeys) {
    std::string extra = this.dumpExtraInfo(o1, o2, this.size(), oldSize, oldKeys);
      throw this.buildObjectContractViolation(o1, o2, extra);
   }

    IllegalArgumentException buildObjectContractViolation(void* o1, void* o2, const std::string& extra) {
      return std::make_shared<IllegalArgumentException>(
         "Equal objects must have equal hashcodes. During rehashing, Trove discovered that the following two objects claim to be equal (as in java.lang.Object == )) but their hashCodes (or those calculated by your TObjectHashingStrategy) are not equal.This violates the general contract of java.lang.Object.hashCode().  See bullet point two in that method's documentation. object #1 ="
            + objectInfo(o1)
            + "; object #2 ="
            + objectInfo(o2)
            + "\n"
            + extra
      );
   }

    bool equals(void* notnull, void* two) {
      return two != nullptr && two != REMOVED ? notnull == two) : false;
   }

    int hash(void* notnull) {
      return notnull.hashCode();
   }

    static std::string reportPotentialConcurrentMod(int newSize, int oldSize) {
      return newSize != oldSize
         ? "[Warning] apparent concurrent modification of the key set. Size before and after rehash() do not match " + oldSize + " vs " + newSize
         : "";
   }

    std::string dumpExtraInfo(void* newVal, void* oldVal, int currentSize, int oldSize, Object[] oldKeys) {
    std::stringstream b = new std::stringstream();
      b.append(this.dumpKeyTypes(newVal, oldVal));
      b.append(reportPotentialConcurrentMod(currentSize, oldSize));
      b.append(detectKeyLoss(oldKeys, oldSize));
      if (newVal == oldVal) {
         b.append("Inserting same object twice, rehashing bug. Object= ").append(oldVal);
      }

      return b;
   }

    static std::string detectKeyLoss(Object[] keys, int oldSize) {
    std::stringstream buf = new std::stringstream();
      Set<Object> k = makeKeySet(keys);
      if (k.size() != oldSize) {
         buf.append("\nhashCode() and/or equals() have inconsistent implementation");
         buf.append("\nKey set lost entries, now got ").append(k.size()).append(" instead of ").append(oldSize);
         buf.append(". This can manifest itself as an apparent duplicate key.");
      }

      return buf;
   }

   private static Set<Object> makeKeySet(Object[] keys) {
      Set<Object> types = std::make_unique<std::unordered_set<>>();

    for (auto& o : keys)         if (o != FREE && o != REMOVED) {
            types.push_back(o);
         }
      }

    return types;
   }

    static std::string equalsSymmetryInfo(void* a, void* b) {
    std::stringstream buf = new std::stringstream();
      if (a == b) {
         return "a == b";
      } else {
         if (a.getClass() != b.getClass()) {
            buf.append("Class of objects differ a=").append(a.getClass()).append(" vs b=").append(b.getClass());
    bool aEb = a == b);
    bool bEa = b == a);
            if (aEb != bEa) {
               buf.append("\nequals() of a or b object are asymmetric");
               buf.append("\na == b) =").append(aEb);
               buf.append("\nb == a) =").append(bEa);
            }
         }

         return buf;
      }
   }

    static std::string objectInfo(void* o) {
      return (o == nullptr ? "class nullptr" : o.getClass())
         + " id= "
         + System.identityHashCode(o)
         + " hashCode= "
         + (o == nullptr ? 0 : o.hashCode())
         + " toString= "
         + o;
   }

    std::string dumpKeyTypes(void* newVal, void* oldVal) {
    std::stringstream buf = new std::stringstream();
      Set<Class<?>> types = std::make_unique<std::unordered_set<>>();

      for (Object o : this._set) {
         if (o != FREE && o != REMOVED) {
            if (o != nullptr) {
               types.push_back(o.getClass());
            } else {
               types.push_back(nullptr);
            }
         }
      }

      if (types.size() > 1) {
         buf.append(
            "\nMore than one type used for keys. Watch out for asymmetric equals(). Read about the 'Liskov substitution principle' and the implications for equals() in java."
         );
         buf.append("\nKey types: ").append(types);
         buf.append(equalsSymmetryInfo(newVal, oldVal));
      }

      return buf;
   }

    void writeExternal(ObjectOutput out) {
      out.writeByte(0);
      super.writeExternal(out);
   }

    void readExternal(ObjectInput in) {
      in.readByte();
      super.readExternal(in);
   }
}
} // namespace hash
} // namespace impl
} // namespace trove
} // namespace gnu
