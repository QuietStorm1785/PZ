#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/Pool.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace animation {


class TwistableBoneTransform : public BoneTransform {
public:
    float BlendWeight = 0.0F;
    float Twist = 0.0F;
   private static const Pool<TwistableBoneTransform> s_pool = std::make_shared<Pool>(TwistableBoneTransform::new);

    protected TwistableBoneTransform() {
   }

    static TwistableBoneTransform alloc() {
      return (TwistableBoneTransform)s_pool.alloc();
   }
}
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
