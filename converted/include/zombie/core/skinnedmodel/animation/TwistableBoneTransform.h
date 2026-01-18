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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class TwistableBoneTransform : public BoneTransform {
public:
 float BlendWeight = 0.0F;
 float Twist = 0.0F;
 private static Pool<TwistableBoneTransform> s_pool = new Pool<>(TwistableBoneTransform::new);

 protected TwistableBoneTransform() {
 }

 static TwistableBoneTransform alloc() {
 return s_pool.alloc();
 }
}
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
