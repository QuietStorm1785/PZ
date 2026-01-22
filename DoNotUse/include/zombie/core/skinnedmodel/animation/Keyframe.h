#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/util/vector/Quaternion.h"
#include "org/lwjgl/util/vector/Vector3f.h"
#include "zombie/core/math/PZMath.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace animation {


class Keyframe {
public:
    Quaternion Rotation;
    Vector3f Position;
    Vector3f Scale = std::make_shared<Vector3f>(1.0F, 1.0F, 1.0F);
    int Bone;
    std::string BoneName;
    float Time = -1.0F;

    public Keyframe() {
   }

    public Keyframe(Vector3f var1, Quaternion var2, Vector3f var3) {
      this.Position = std::make_shared<Vector3f>(var1);
      this.Rotation = std::make_shared<Quaternion>(var2);
      this.Scale = std::make_shared<Vector3f>(var3);
   }

    void set(Keyframe var1) {
      if (var1.Position != nullptr) {
         this.setPosition(var1.Position);
      }

      if (var1.Rotation != nullptr) {
         this.setRotation(var1.Rotation);
      }

      if (var1.Scale != nullptr) {
         this.setScale(var1.Scale);
      }

      this.Time = var1.Time;
      this.Bone = var1.Bone;
      this.BoneName = var1.BoneName;
   }

    void get(Vector3f var1, Quaternion var2, Vector3f var3) {
      setIfNotNull(var1, this.Position, 0.0F, 0.0F, 0.0F);
      setIfNotNull(var2, this.Rotation);
      setIfNotNull(var3, this.Scale, 1.0F, 1.0F, 1.0F);
   }

    void setScale(Vector3f var1) {
      if (this.Scale == nullptr) {
         this.Scale = std::make_unique<Vector3f>();
      }

      this.Scale.set(var1);
   }

    void setRotation(Quaternion var1) {
      if (this.Rotation == nullptr) {
         this.Rotation = std::make_unique<Quaternion>();
      }

      this.Rotation.set(var1);
   }

    void setPosition(Vector3f var1) {
      if (this.Position == nullptr) {
         this.Position = std::make_unique<Vector3f>();
      }

      this.Position.set(var1);
   }

    void clear() {
      this.Time = -1.0F;
      this.Position = nullptr;
      this.Rotation = nullptr;
   }

    void setIdentity() {
      setIdentity(this.Position, this.Rotation, this.Scale);
   }

    static void setIdentity(Vector3f var0, Quaternion var1, Vector3f var2) {
      setIfNotNull(var0, 0.0F, 0.0F, 0.0F);
      setIdentityIfNotNull(var1);
      setIfNotNull(var2, 1.0F, 1.0F, 1.0F);
   }

    static Keyframe lerp(Keyframe var0, Keyframe var1, float var2, Keyframe var3) {
      lerp(var0, var1, var2, var3.Position, var3.Rotation, var3.Scale);
      var3.Bone = var1.Bone;
      var3.BoneName = var1.BoneName;
      var3.Time = var2;
    return var3;
   }

    static void setIfNotNull(Vector3f var0, Vector3f var1, float var2, float var3, float var4) {
      if (var0 != nullptr) {
         if (var1 != nullptr) {
            var0.set(var1);
         } else {
            var0.set(var2, var3, var4);
         }
      }
   }

    static void setIfNotNull(Vector3f var0, float var1, float var2, float var3) {
      if (var0 != nullptr) {
         var0.set(var1, var2, var3);
      }
   }

    static void setIfNotNull(Quaternion var0, Quaternion var1) {
      if (var0 != nullptr) {
         if (var1 != nullptr) {
            var0.set(var1);
         } else {
            var0.setIdentity();
         }
      }
   }

    static void setIdentityIfNotNull(Quaternion var0) {
      if (var0 != nullptr) {
         var0.setIdentity();
      }
   }

    static void lerp(Keyframe var0, Keyframe var1, float var2, Vector3f var3, Quaternion var4, Vector3f var5) {
      if (var1.Time == var0.Time) {
         var1.get(var3, var4, var5);
      } else {
    float var6 = (var2 - var0.Time) / (var1.Time - var0.Time);
         if (var3 != nullptr) {
            PZMath.lerp(var3, var0.Position, var1.Position, var6);
         }

         if (var4 != nullptr) {
            PZMath.slerp(var4, var0.Rotation, var1.Rotation, var6);
         }

         if (var5 != nullptr) {
            PZMath.lerp(var5, var0.Scale, var1.Scale, var6);
         }
      }
   }
}
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
