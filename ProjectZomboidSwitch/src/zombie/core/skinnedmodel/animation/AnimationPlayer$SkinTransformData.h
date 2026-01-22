#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/util/vector/Matrix4f.h"
#include "zombie/core/skinnedmodel/model/SkinningData.h"
#include "zombie/util/Pool.h"
#include "zombie/util/PooledObject.h"
#include "zombie/util/list/PZArrayUtil.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace animation {


class AnimationPlayer {
public:
   public Matrix4f[] transforms;
    SkinningData m_skinnedTo;
    bool dirty;
   private AnimationPlayer$SkinTransformData m_next;
   private static Pool<AnimationPlayer$SkinTransformData> s_pool = std::make_shared<Pool>(AnimationPlayer$SkinTransformData::new);

   private AnimationPlayer$SkinTransformData() {
   }

    void setSkinnedTo(SkinningData var1) {
      if (this.m_skinnedTo != var1) {
         this.dirty = true;
         this.m_skinnedTo = var1;
         this.transforms = (Matrix4f[])PZArrayUtil.newInstance(Matrix4f.class, this.transforms, var1.numBones(), Matrix4f::new);
      }
   }

   public static AnimationPlayer$SkinTransformData alloc(SkinningData var0) {
      AnimationPlayer$SkinTransformData var1 = (AnimationPlayer$SkinTransformData)s_pool.alloc();
      var1.setSkinnedTo(var0);
      var1.dirty = true;
    return var1;
   }
}
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
