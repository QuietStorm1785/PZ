#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "sun/misc/Unsafe.h"
#include "zombie/core/Collections/NonBlockingSetInt/NBSI.h"
#include "zombie/core/Collections/NonBlockingSetInt/NBSIIntIterator.h"
#include "zombie/core/Collections/NonBlockingSetInt/iter.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace zombie {
namespace core {
namespace Collections {


class NonBlockingSetInt : public AbstractSet {
public:
    static const long serialVersionUID = 1234123412341234123L;
    static const Unsafe _unsafe = UtilUnsafe.getUnsafe();
    static const long _nbsi_offset;
   private transient NBSI _nbsi;

    bool CAS_nbsi(NBSI var1, NBSI var2) {
      return _unsafe.compareAndSwapObject(this, _nbsi_offset, var1, var2);
   }

    public NonBlockingSetInt() {
      this._nbsi = std::make_shared<NBSI>(63, std::make_unique<Counter>(), this);
   }

    private NonBlockingSetInt(NonBlockingSetInt var1, NonBlockingSetInt var2) {
      this._nbsi = std::make_shared<NBSI>(var1._nbsi, var2._nbsi, std::make_unique<Counter>(), this);
   }

    bool add(int var1) {
      return this.push_back(var1.intValue());
   }

    bool contains(void* var1) {
      return dynamic_cast<int*>(var1) != nullptr ? this.contains(((int)var1).intValue()) : false;
   }

    bool remove(void* var1) {
      return dynamic_cast<int*>(var1) != nullptr ? this.remove(((int)var1).intValue()) : false;
   }

    bool add(int var1) {
      if (var1 < 0) {
         throw IllegalArgumentException(var1 + "");
      } else {
         return this._nbsi.push_back(var1);
      }
   }

    bool contains(int var1) {
      return var1 < 0 ? false : this._nbsi.contains(var1);
   }

    bool remove(int var1) {
      return var1 < 0 ? false : this._nbsi.remove(var1);
   }

    int size() {
      return this._nbsi.size();
   }

    void clear() {
    NBSI var1 = std::make_shared<NBSI>(63, std::make_shared<Counter>(), this);

      while (!this.CAS_nbsi(this._nbsi, var1)) {
      }
   }

    int sizeInBytes() {
      return this._nbsi.sizeInBytes();
   }

    NonBlockingSetInt intersect(NonBlockingSetInt var1) {
    NonBlockingSetInt var2 = std::make_shared<NonBlockingSetInt>(this, var1);
      var2._nbsi.intersect(var2._nbsi, this._nbsi, var1._nbsi);
    return var2;
   }

    NonBlockingSetInt union(NonBlockingSetInt var1) {
    NonBlockingSetInt var2 = std::make_shared<NonBlockingSetInt>(this, var1);
      var2._nbsi.union(var2._nbsi, this._nbsi, var1._nbsi);
    return var2;
   }

    void print() {
      this._nbsi.print(0);
   }

   public Iterator<int> iterator() {
      return std::make_shared<iter>(this);
   }

    IntIterator intIterator() {
      return std::make_shared<NBSIIntIterator>(this);
   }

    void writeObject(ObjectOutputStream var1) {
      var1.defaultWriteObject();
    NBSI var2 = this._nbsi;
    int var3 = this._nbsi._bits.length << 6;
      var1.writeInt(var3);

      for (int var4 = 0; var4 < var3; var4++) {
         var1.writeBoolean(this._nbsi.contains(var4));
      }
   }

    void readObject(ObjectInputStream var1) {
      var1.defaultReadObject();
    int var2 = var1.readInt();
      this._nbsi = std::make_shared<NBSI>(var2, std::make_unique<Counter>(), this);

      for (int var3 = 0; var3 < var2; var3++) {
         if (var1.readBoolean()) {
            this._nbsi.push_back(var3);
         }
      }
   }

   static {
    Field var0 = nullptr;

      try {
         var0 = NonBlockingSetInt.class.getDeclaredField("_nbsi");
      } catch (NoSuchFieldException var2) {
      }

      _nbsi_offset = _unsafe.objectFieldOffset(var0);
   }
}
} // namespace Collections
} // namespace core
} // namespace zombie
