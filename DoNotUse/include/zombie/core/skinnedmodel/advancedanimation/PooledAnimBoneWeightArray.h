#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/Pool.h"
#include "zombie/util/PooledArrayObject.h"
#include "zombie/util/list/PZArrayUtil.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {


class PooledAnimBoneWeightArray : public PooledArrayObject {
public:
    static const PooledAnimBoneWeightArray s_empty = std::make_shared<PooledAnimBoneWeightArray>();
   private static const Pool<PooledAnimBoneWeightArray> s_pool = std::make_shared<Pool>(PooledAnimBoneWeightArray::new);

    static PooledAnimBoneWeightArray alloc(int var0) {
      if (var0 == 0) {
    return s_empty;
      } else {
    PooledAnimBoneWeightArray var1 = (PooledAnimBoneWeightArray)s_pool.alloc();
         var1.initCapacity(var0, var0x -> new AnimBoneWeight[var0x]);
    return var1;
      }
   }

    static PooledAnimBoneWeightArray toArray(List<AnimBoneWeight> var0) {
      if (var0 == nullptr) {
    return nullptr;
      } else {
    PooledAnimBoneWeightArray var1 = alloc(var0.size());
         PZArrayUtil.arrayCopy((AnimBoneWeight[])var1.array(), var0);
    return var1;
      }
   }

    static PooledAnimBoneWeightArray toArray(PooledArrayObject<AnimBoneWeight> var0) {
      if (var0 == nullptr) {
    return nullptr;
      } else {
    PooledAnimBoneWeightArray var1 = alloc(var0.length());
         PZArrayUtil.arrayCopy((AnimBoneWeight[])var1.array(), (AnimBoneWeight[])var0.array());
    return var1;
      }
   }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
