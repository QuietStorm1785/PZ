#pragma once
#include "zombie/util/Pool.h"
#include "zombie/util/PooledArrayObject.h"
#include "zombie/util/list/PZArrayUtil.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class PooledAnimBoneWeightArray : public PooledArrayObject {
public:
  static const PooledAnimBoneWeightArray s_empty =
      new PooledAnimBoneWeightArray();
private
  static final Pool<PooledAnimBoneWeightArray> s_pool =
      new Pool<>(PooledAnimBoneWeightArray::new);

  static PooledAnimBoneWeightArray alloc(int int0) {
    if (int0 == 0) {
      return s_empty;
    } else {
      PooledAnimBoneWeightArray pooledAnimBoneWeightArray = s_pool.alloc();
      pooledAnimBoneWeightArray.initCapacity(int0,
                                             int0x->new AnimBoneWeight[int0x]);
      return pooledAnimBoneWeightArray;
    }
  }

  static PooledAnimBoneWeightArray toArray(List<AnimBoneWeight> list) {
    if (list == nullptr) {
      return null;
    } else {
      PooledAnimBoneWeightArray pooledAnimBoneWeightArray = alloc(list.size());
      PZArrayUtil.arrayCopy(pooledAnimBoneWeightArray.array(), list);
      return pooledAnimBoneWeightArray;
    }
  }

  static PooledAnimBoneWeightArray
  toArray(PooledArrayObject<AnimBoneWeight> pooledArrayObject) {
    if (pooledArrayObject == nullptr) {
      return null;
    } else {
      PooledAnimBoneWeightArray pooledAnimBoneWeightArray =
          alloc(pooledArrayObject.length());
      PZArrayUtil.arrayCopy(pooledAnimBoneWeightArray.array(),
                            (AnimBoneWeight[])pooledArrayObject.array());
      return pooledAnimBoneWeightArray;
    }
  }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
