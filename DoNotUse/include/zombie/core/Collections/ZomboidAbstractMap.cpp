#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Collections/ZomboidAbstractMap/1.h"
#include "zombie/core/Collections/ZomboidAbstractMap/2.h"
#include <algorithm>
#include <iterator>

namespace zombie {
namespace core {
namespace Collections {


class ZomboidAbstractMap {
public:
   transient volatile Set<K> keySet = nullptr;
   transient volatile Collection<V> values = nullptr;

    protected ZomboidAbstractMap() {
   }

    int size() {
      return this.entrySet().size();
   }

    bool isEmpty() {
      return this.size() == 0;
   }

    bool containsValue(void* var1) {
    Iterator var2 = this.entrySet().iterator();
      if (var1 == nullptr) {
         while (var2.hasNext()) {
    Entry var4 = (Entry)var2.next();
            if (var4.getValue() == nullptr) {
    return true;
            }
         }
      } else {
         while (var2.hasNext()) {
    Entry var3 = (Entry)var2.next();
            if (var1 == var3.getValue())) {
    return true;
            }
         }
      }

    return false;
   }

    bool containsKey(void* var1) {
    Iterator var2 = this.entrySet().iterator();
      if (var1 == nullptr) {
         while (var2.hasNext()) {
    Entry var4 = (Entry)var2.next();
            if (var4.getKey() == nullptr) {
    return true;
            }
         }
      } else {
         while (var2.hasNext()) {
    Entry var3 = (Entry)var2.next();
            if (var1 == var3.getKey())) {
    return true;
            }
         }
      }

    return false;
   }

    V get(void* var1) {
    Iterator var2 = this.entrySet().iterator();
      if (var1 == nullptr) {
         while (var2.hasNext()) {
    Entry var4 = (Entry)var2.next();
            if (var4.getKey() == nullptr) {
               return (V)var4.getValue();
            }
         }
      } else {
         while (var2.hasNext()) {
    Entry var3 = (Entry)var2.next();
            if (var1 == var3.getKey())) {
               return (V)var3.getValue();
            }
         }
      }

    return nullptr;
   }

    V put(K var1, V var2) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    V remove(void* var1) {
    Iterator var2 = this.entrySet().iterator();
    Entry var3 = nullptr;
      if (var1 == nullptr) {
         while (var3 == nullptr && var2.hasNext()) {
    Entry var5 = (Entry)var2.next();
            if (var5.getKey() == nullptr) {
               var3 = var5;
            }
         }
      } else {
         while (var3 == nullptr && var2.hasNext()) {
    Entry var4 = (Entry)var2.next();
            if (var1 == var4.getKey())) {
               var3 = var4;
            }
         }
      }

    void* var6 = nullptr;
      if (var3 != nullptr) {
         var6 = var3.getValue();
         var2.remove();
      }

      return (V)var6;
   }

    void putAll(Map<? extends, ? extends) {
      for (Entry var3 : var1.entrySet()) {
         this.put((K)var3.getKey(), (V)var3.getValue());
      }
   }

    void clear() {
      this.entrySet().clear();
   }

   public Set<K> keySet() {
      if (this.keySet == nullptr) {
         this.keySet = std::make_shared<1>(this);
      }

      return this.keySet;
   }

   public Collection<V> values() {
      if (this.values == nullptr) {
         this.values = std::make_shared<2>(this);
      }

      return this.values;
   }

   public abstract Set<Entry<K, V>> entrySet();

    bool equals(void* var1) {
      if (var1 == this) {
    return true;
      } else if (!(dynamic_cast<Map*>(var1) != nullptr var2)) {
    return false;
      } else if (var2.size() != this.size()) {
    return false;
      } else {
         try {
            for (Entry var4 : this.entrySet()) {
    void* var5 = var4.getKey();
    void* var6 = var4.getValue();
               if (var6 == nullptr) {
                  if (var2.get(var5) != nullptr || !var2.containsKey(var5)) {
    return false;
                  }
               } else if (!var6 == var2.get(var5))) {
    return false;
               }
            }

    return true;
         } catch (ClassCastException var7) {
    return false;
         } catch (NullPointerException var8) {
    return false;
         }
      }
   }

    int hashCode() {
    int var1 = 0;
    Iterator var2 = this.entrySet().iterator();

      while (var2.hasNext()) {
         var1 += ((Entry)var2.next()).hashCode();
      }

    return var1;
   }

    std::string toString() {
    Iterator var1 = this.entrySet().iterator();
      if (!var1.hasNext()) {
         return "{}";
      } else {
    std::stringstream var2 = new std::stringstream();
         var2.append('{');

         while (true) {
    Entry var3 = (Entry)var1.next();
    void* var4 = var3.getKey();
    void* var5 = var3.getValue();
            var2.append(var4 == this ? "(this Map)" : var4);
            var2.append('=');
            var2.append(var5 == this ? "(this Map)" : var5);
            if (!var1.hasNext()) {
               return var2.append('}');
            }

            var2.append(", ");
         }
      }
   }

    void* clone() {
    ZomboidAbstractMap var1 = (ZomboidAbstractMap)super.clone();
      var1.keySet = nullptr;
      var1.values = nullptr;
    return var1;
   }

    static bool eq(void* var0, void* var1) {
    return var0 = = nullptr ? var1 == nullptr : var0 == var1);
   }
}
} // namespace Collections
} // namespace core
} // namespace zombie
