#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Rand.h"
#include <algorithm>
#include <iterator>

namespace zombie {
namespace network {


class IsoObjectID {
public:
    static const short incorrect = -1;
   private const ConcurrentHashMap<int16_t, T> IDToObjectMap = std::make_unique<ConcurrentHashMap<>>();
    const std::string objectType;
    short nextID = (short)Rand.Next(32766);

    public IsoObjectID(Class<T> var1) {
      this.objectType = var1.getSimpleName();
   }

    void put(short var1, T var2) {
      if (var1 != -1) {
         this.IDToObjectMap.put(var1, (T)var2);
      }
   }

    void remove(short var1) {
      this.IDToObjectMap.remove(var1);
   }

    void remove(T var1) {
      this.IDToObjectMap.values().remove(var1);
   }

    T get(short var1) {
      return this.IDToObjectMap.get(var1);
   }

    int size() {
      return this.IDToObjectMap.size();
   }

    void clear() {
      this.IDToObjectMap.clear();
   }

    short allocateID() {
      this.nextID++;
      if (this.nextID == -1) {
         this.nextID++;
      }

      return this.nextID;
   }

   public Iterator<T> iterator() {
      return this.IDToObjectMap.values().iterator();
   }

    void getObjects(Collection<T> var1) {
      var1.addAll(this.IDToObjectMap.values());
   }
}
} // namespace network
} // namespace zombie
