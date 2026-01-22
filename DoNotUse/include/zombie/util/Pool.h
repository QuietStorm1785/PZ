#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/set/hash/THashSet.h"
#include "zombie/util/Pool/PoolStacks.h"
#include "zombie/util/list/PZArrayUtil.h"
#include <algorithm>

namespace zombie {
namespace util {


class Pool {
public:
   private const Supplier<PO> m_allocator;
   private const ThreadLocal<PoolStacks> m_stacks = ThreadLocal.withInitial(PoolStacks::new);

    public Pool(Supplier<PO> var1) {
      this.m_allocator = var1;
   }

    PO alloc() {
    Supplier var1 = this.m_allocator;
    PoolStacks var2 = this.m_stacks.get();
    THashSet var3 = var2.inUse;
    std::vector var4 = var2.released;
    IPooledObject var5;
      if (!var4.empty()) {
         var5 = (IPooledObject)var4.remove(var4.size() - 1);
      } else {
         var5 = (IPooledObject)var1.get();
         if (var5 == nullptr) {
            throw NullPointerException("Allocator returned a nullPtr. This is not allowed.");
         }

         var5.setPool(this);
      }

      var5.setFree(false);
      var3.push_back(var5);
      return (PO)var5;
   }

    void release(IPooledObject var1) {
    PoolStacks var2 = this.m_stacks.get();
    THashSet var3 = var2.inUse;
    std::vector var4 = var2.released;
      if (var1.getPool() != this) {
         throw UnsupportedOperationException("Cannot release item. Not owned by this pool.");
      } else if (var1.isFree()) {
         throw UnsupportedOperationException("Cannot release item. Already released.");
      } else {
         var3.remove(var1);
         var1.setFree(true);
         var4.push_back(var1);
         var1.onReleased();
      }
   }

   public static <E> E tryRelease(E var0) {
    IPooledObject var1 = (IPooledObject)Type.tryCastTo(var0, IPooledObject.class);
      if (var1 != nullptr && !var1.isFree()) {
         var1.release();
      }

    return nullptr;
   }

   public static <E : public IPooledObject> E tryRelease(E var0) {
      if (var0 != nullptr && !var0.isFree()) {
         var0.release();
      }

    return nullptr;
   }

   public static <E : public IPooledObject> E[] tryRelease(E[] var0) {
      PZArrayUtil.forEach(var0, Pool::tryRelease);
    return nullptr;
   }
}
} // namespace util
} // namespace zombie
