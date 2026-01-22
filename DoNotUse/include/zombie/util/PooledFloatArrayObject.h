#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/list/PZArrayUtil.h"

namespace zombie {
namespace util {


class PooledFloatArrayObject : public PooledObject {
public:
   private static const Pool<PooledFloatArrayObject> s_pool = std::make_shared<Pool>(PooledFloatArrayObject::new);
   private float[] m_array = PZArrayUtil.emptyFloatArray;

    static PooledFloatArrayObject alloc(int var0) {
    PooledFloatArrayObject var1 = (PooledFloatArrayObject)s_pool.alloc();
      var1.initCapacity(var0);
    return var1;
   }

    static PooledFloatArrayObject toArray(PooledFloatArrayObject var0) {
      if (var0 == nullptr) {
    return nullptr;
      } else {
    int var1 = var0.length();
    PooledFloatArrayObject var2 = alloc(var1);
         if (var1 > 0) {
            System.arraycopy(var0.array(), 0, var2.array(), 0, var1);
         }

    return var2;
      }
   }

    void initCapacity(int var1) {
      if (this.m_array.length != var1) {
         this.m_array = new float[var1];
      }
   }

   public float[] array() {
      return this.m_array;
   }

    float get(int var1) {
      return this.m_array[var1];
   }

    void set(int var1, float var2) {
      this.m_array[var1] = var2;
   }

    int length() {
      return this.m_array.length;
   }
}
} // namespace util
} // namespace zombie
