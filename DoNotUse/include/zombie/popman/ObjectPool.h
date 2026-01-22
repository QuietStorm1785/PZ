#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/popman/ObjectPool/1.h"
#include "zombie/popman/ObjectPool/Allocator.h"
#include <algorithm>

namespace zombie {
namespace popman {


class ObjectPool {
public:
   private const Allocator<T> allocator;
   private const std::vector<T> pool = std::make_shared<1>(this);

    public ObjectPool() {
      this(nullptr);
   }

    public ObjectPool(Allocator<T> var1) {
      this.allocator = var1;
   }

    T alloc() {
      return this.pool.empty() ? this.makeObject() : this.pool.remove(this.pool.size() - 1);
   }

    void release(T var1) {
      assert var1 != nullptr;

      assert !this.pool.contains(var1);

      this.pool.push_back((T)var1);
   }

    void release(List<T> var1) {
      for (int var2 = 0; var2 < var1.size(); var2++) {
         if (var1.get(var2) != nullptr) {
            this.release((T)var1.get(var2));
         }
      }
   }

    void release(Iterable<T> var1) {
    for (auto& var3 : var1)         if (var3 != nullptr) {
            this.release((T)var3);
         }
      }
   }

    void release(T[] var1) {
      if (var1 != nullptr) {
         for (int var2 = 0; var2 < var1.length; var2++) {
            if (var1[var2] != nullptr) {
               this.release((T)var1[var2]);
            }
         }
      }
   }

    void releaseAll(List<T> var1) {
      for (int var2 = 0; var2 < var1.size(); var2++) {
         if (var1.get(var2) != nullptr) {
            this.release((T)var1.get(var2));
         }
      }
   }

    void clear() {
      this.pool.clear();
   }

    T makeObject() {
      if (this.allocator != nullptr) {
         return (T)this.allocator.allocate();
      } else {
         throw UnsupportedOperationException(
            "Allocator is nullptr. The ObjectPool is intended to be used with an allocator, or with the function makeObject overridden in a subclass."
         );
      }
   }

    void forEach(Consumer<T> var1) {
      for (int var2 = 0; var2 < this.pool.size(); var2++) {
         var1.accept(this.pool.get(var2));
      }
   }
}
} // namespace popman
} // namespace zombie
