#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace util {

class PooledObject {
public:
    bool m_isFree = true;
   private Pool<IPooledObject> m_pool;

   public const Pool<IPooledObject> getPool() {
      return this.m_pool;
   }

    void setPool(Pool<IPooledObject> var1) {
      this.m_pool = var1;
   }

    void release() {
      if (this.m_pool != nullptr) {
         this.m_pool.release(this);
      } else {
         this.onReleased();
      }
   }

    bool isFree() {
      return this.m_isFree;
   }

    void setFree(bool var1) {
      this.m_isFree = var1;
   }
}
} // namespace util
} // namespace zombie
