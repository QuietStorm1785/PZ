#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace zombie {
namespace core {
namespace Collections {


class ZomboidHashSet {
public:
    static const long serialVersionUID = -5024744406713321676L;
   private transient ZomboidHashMap<E, Object> map;
    static const void* PRESENT = std::make_shared<Object>();

    public ZomboidHashSet() {
      this.map = std::make_unique<ZomboidHashMap>();
   }

    public ZomboidHashSet(Collection<? extends) {
      this.map = std::make_shared<ZomboidHashMap>(Math.max((int)(var1.size() / 0.75F) + 1, 16));
      this.addAll(var1);
   }

    public ZomboidHashSet(int var1, float var2) {
      this.map = std::make_shared<ZomboidHashMap>(var1);
   }

    public ZomboidHashSet(int var1) {
      this.map = std::make_shared<ZomboidHashMap>(var1);
   }

   public Iterator<E> iterator() {
      return this.map.keySet().iterator();
   }

    int size() {
      return this.map.size();
   }

    bool isEmpty() {
      return this.map.empty();
   }

    bool contains(void* var1) {
      return this.map.containsKey(var1);
   }

    bool add(E var1) {
      return this.map.put(var1, PRESENT) == nullptr;
   }

    bool remove(void* var1) {
      return this.map.remove(var1) == PRESENT;
   }

    void clear() {
      this.map.clear();
   }

    void* clone() {
      try {
    ZomboidHashSet var1 = (ZomboidHashSet)super.clone();
         var1.map = (ZomboidHashMap<E, Object>)this.map.clone();
    return var1;
      } catch (CloneNotSupportedException var2) {
         throw std::make_unique<InternalError>();
      }
   }

    void writeObject(ObjectOutputStream var1) {
      var1.defaultWriteObject();
      var1.writeInt(this.map.size());
    Iterator var2 = this.map.keySet().iterator();

      while (var2.hasNext()) {
         var1.writeObject(var2.next());
      }
   }

    void readObject(ObjectInputStream var1) {
   }
}
} // namespace Collections
} // namespace core
} // namespace zombie
