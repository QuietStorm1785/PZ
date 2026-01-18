#pragma once
#include "zombie/util/AbstractIntCollection.h"
#include "zombie/util/IntCollection.h"
#include "zombie/util/IntIterator.h"
#include "zombie/util/hash/DefaultIntHashFunction.h"
#include "zombie/util/util/Exceptions.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace util {
namespace list {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class AbstractIntList : public AbstractIntCollection {
public:
protected
  AbstractIntList() {}

  bool add(int int0) {
    this.add(this.size(), int0);
    return true;
  }

  void add(int var1, int var2) { Exceptions.unsupported("add"); }

  bool addAll(int int0, IntCollection intCollection) {
    if (int0 < 0 || int0 > this.size()) {
      Exceptions.indexOutOfBounds(int0, 0, this.size());
    }

    IntIterator intIterator = intCollection.iterator();

    bool boolean0;
    for (boolean0 = intIterator.hasNext(); intIterator.hasNext(); int0++) {
      this.add(int0, intIterator.next());
    }

    return boolean0;
  }

  int indexOf(int int0) { return this.indexOf(0, int0); }

  int indexOf(int int0, int int1) {
    IntListIterator intListIterator = this.listIterator(int0);

    while (intListIterator.hasNext()) {
      if (intListIterator.next() == int1) {
        return intListIterator.previousIndex();
      }
    }

    return -1;
  }

  IntIterator iterator() { return this.listIterator(); }

  int lastIndexOf(int int0) {
    IntListIterator intListIterator = this.listIterator(this.size());

    while (intListIterator.hasPrevious()) {
      if (intListIterator.previous() == int0) {
        return intListIterator.nextIndex();
      }
    }

    return -1;
  }

  int lastIndexOf(int int0, int int1) {
    IntListIterator intListIterator = this.listIterator(int0);

    while (intListIterator.hasPrevious()) {
      if (intListIterator.previous() == int1) {
        return intListIterator.nextIndex();
      }
    }

    return -1;
  }

  IntListIterator listIterator() { return this.listIterator(0); }

  IntListIterator listIterator(final int) {
    if (int0 < 0 || int0 > this.size()) {
      Exceptions.indexOutOfBounds(int0, 0, this.size());
    }

    return std::make_unique<IntListIterator>() {
      int ptr = int0;
      int lptr = -1;

      bool hasNext() { return this.ptr < AbstractIntList.this.size(); }

      int next() {
        if (this.ptr == AbstractIntList.this.size()) {
          Exceptions.endOfIterator();
        }

        this.lptr = this.ptr++;
        return AbstractIntList.this.get(this.lptr);
      }

      void remove() {
        if (this.lptr == -1) {
          Exceptions.noElementToRemove();
        }

        AbstractIntList.this.removeElementAt(this.lptr);
        if (this.lptr < this.ptr) {
          this.ptr--;
        }

        this.lptr = -1;
      }

      void add(int int0x) {
        AbstractIntList.this.add(this.ptr++, int0x);
        this.lptr = -1;
      }

      bool hasPrevious() { return this.ptr > 0; }

      int nextIndex() { return this.ptr; }

      int previous() {
        if (this.ptr == 0) {
          Exceptions.startOfIterator();
        }

        this.ptr--;
        this.lptr = this.ptr;
        return AbstractIntList.this.get(this.ptr);
      }

      int previousIndex() { return this.ptr - 1; }

      void set(int int0x) {
        if (this.lptr == -1) {
          Exceptions.noElementToSet();
        }

        AbstractIntList.this.set(this.lptr, int0x);
      }
    };
  }

  int removeElementAt(int var1) {
    Exceptions.unsupported("removeElementAt");
    throw std::make_unique<RuntimeException>();
  }

  bool equals(void *object) {
    if (this == object) {
      return true;
    } else if (!(object instanceof IntList)) {
      return false;
    } else {
      IntListIterator intListIterator0 = this.listIterator();
      IntListIterator intListIterator1 = ((IntList)object).listIterator();

      while (intListIterator0.hasNext() && intListIterator1.hasNext()) {
        if (intListIterator0.next() != intListIterator1.next()) {
          return false;
        }
      }

      return !intListIterator0.hasNext() && !intListIterator1.hasNext();
    }
  }

  int hashCode() {
    int int0 = 1;
    IntIterator intIterator = this.iterator();

    while (intIterator.hasNext()) {
      int0 =
          31 * int0 + DefaultIntHashFunction.INSTANCE.hash(intIterator.next());
    }

    return int0;
  }
}
} // namespace list
} // namespace util
} // namespace zombie
