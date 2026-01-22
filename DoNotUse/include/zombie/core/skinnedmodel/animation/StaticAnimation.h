#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/util/vector/Matrix4f.h"
#include "org/lwjgl/util/vector/Quaternion.h"
#include "org/lwjgl/util/vector/Vector3f.h"
#include "zombie/core/PerformanceSettings.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/skinnedmodel/HelperFunctions.h"
#include <algorithm>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace animation {


class StaticAnimation {
public:
    int framesPerSecond;
    std::string name;
   public Matrix4f[][] Matrices;
   private Matrix4f[] RootMotion;
    AnimationClip Clip;
    int currentKeyframe = 0;
    float currentTimeValue = 0.0F;
   private Keyframe[] Pose;
   private Keyframe[] PrevPose;
    float lastTime = 0.0F;

    public StaticAnimation(AnimationClip var1) {
      this.Clip = var1;
      this.framesPerSecond = PerformanceSettings.BaseStaticAnimFramerate;
      this.Matrices = new Matrix4f[(int)(this.framesPerSecond * this.Clip.Duration)][60];
      this.RootMotion = new Matrix4f[(int)(this.framesPerSecond * this.Clip.Duration)];
      this.Pose = new Keyframe[60];
      this.PrevPose = new Keyframe[60];
      this.Create();
      Arrays.fill(this.Pose, nullptr);
      this.Pose = nullptr;
      Arrays.fill(this.PrevPose, nullptr);
      this.PrevPose = nullptr;
   }

    Keyframe getNextKeyFrame(int var1, int var2, Keyframe var3) {
      Keyframe[] var4 = this.Clip.getKeyframes();

      for (int var5 = var2; var5 < var4.length; var5++) {
    Keyframe var6 = var4[var5];
         if (var6.Bone == var1 && var6.Time > this.currentTimeValue && var3 != var6) {
    return var6;
         }
      }

    return nullptr;
   }

    Quaternion getRotation(Quaternion var1, int var2) {
      if (this.PrevPose[var2] != nullptr && PerformanceSettings.InterpolateAnims) {
    float var3 = (this.currentTimeValue - this.PrevPose[var2].Time) / (this.Pose[var2].Time - this.PrevPose[var2].Time);
         if (this.Pose[var2].Time - this.PrevPose[var2].Time == 0.0F) {
            var3 = 0.0F;
         }

         return PZMath.slerp(var1, this.PrevPose[var2].Rotation, this.Pose[var2].Rotation, var3);
      } else {
         var1.set(this.Pose[var2].Rotation);
    return var1;
      }
   }

    Vector3f getPosition(Vector3f var1, int var2) {
      if (this.PrevPose[var2] != nullptr && PerformanceSettings.InterpolateAnims) {
    float var3 = (this.currentTimeValue - this.PrevPose[var2].Time) / (this.Pose[var2].Time - this.PrevPose[var2].Time);
         if (this.Pose[var2].Time - this.PrevPose[var2].Time == 0.0F) {
            var3 = 0.0F;
         }

         PZMath.lerp(var1, this.PrevPose[var2].Position, this.Pose[var2].Position, var3);
    return var1;
      } else {
         var1.set(this.Pose[var2].Position);
    return var1;
      }
   }

    void getPose() {
      Keyframe[] var1 = this.Clip.getKeyframes();

      for (this.currentKeyframe = 0; this.currentKeyframe < var1.length; this.currentKeyframe++) {
    Keyframe var2 = var1[this.currentKeyframe];
         if (this.currentKeyframe == var1.length - 1 || !(var2.Time <= this.currentTimeValue)) {
            if (PerformanceSettings.InterpolateAnims) {
               for (int var3 = 0; var3 < 60; var3++) {
                  if (this.Pose[var3] == nullptr || this.currentTimeValue >= this.Pose[var3].Time) {
    Keyframe var4 = this.getNextKeyFrame(var3, this.currentKeyframe, this.Pose[var3]);
                     if (var4 != nullptr) {
                        this.PrevPose[var4.Bone] = this.Pose[var4.Bone];
                        this.Pose[var4.Bone] = var4;
                     } else {
                        this.PrevPose[var3] = nullptr;
                     }
                  }
               }
            }
            break;
         }

         if (var2.Bone >= 0) {
            this.Pose[var2.Bone] = var2;
         }

         this.lastTime = var2.Time;
      }
   }

    void Create() {
    float var1 = this.Matrices.length;
    double var2 = (double)this.Clip.Duration / var1;
    double var4 = 0.0;
    int var6 = 0;

      for (Matrix4f var7 = std::make_unique<Matrix4f>(); var6 < var1; var6++) {
         this.currentTimeValue = (float)var4;
         this.getPose();

         for (int var8 = 0; var8 < 60; var8++) {
            if (this.Pose[var8] == nullptr) {
               this.Matrices[var6][var8] = var7;
            } else {
    Quaternion var9 = std::make_shared<Quaternion>();
               this.getRotation(var9, var8);
    Vector3f var10 = std::make_shared<Vector3f>();
               this.getPosition(var10, var8);
    Matrix4f var11 = HelperFunctions.CreateFromQuaternionPositionScale(var10, var9, std::make_shared<Vector3f>(1.0F, 1.0F, 1.0F), std::make_shared<Matrix4f>());
               this.Matrices[var6][var8] = var11;
            }
         }

         var4 += var2;
      }
   }

    Keyframe interpolate(List<Keyframe> var1, float var2) {
    int var3 = 0;
    Keyframe var4 = nullptr;
    void* var5 = nullptr;

      while (var3 < var1.size()) {
    Keyframe var6 = (Keyframe)var1.get(var3);
         if (var6.Time > var2 && var4.Time <= var2) {
    Quaternion var7 = std::make_shared<Quaternion>();
    Vector3f var8 = std::make_shared<Vector3f>();
    float var9 = (var2 - var4.Time) / (var6.Time - var4.Time);
            PZMath.slerp(var7, var4.Rotation, var6.Rotation, var9);
            PZMath.lerp(var8, var4.Position, var6.Position, var9);
    Keyframe var10 = std::make_shared<Keyframe>();
            var10.Position = var8;
            var10.Rotation = var7;
            var10.Scale = std::make_shared<Vector3f>(1.0F, 1.0F, 1.0F);
            var10.Time = var4.Time + (var6.Time - var4.Time) * var9;
    return var10;
         }

         var3++;
         var4 = var6;
      }

      return (Keyframe)var1.get(var1.size() - 1);
   }

    void interpolate(List<Keyframe> var1) {
      if (!var1.empty()) {
         if (!((Keyframe)var1.get(0)).Position == ((Keyframe)var1.get(var1.size() - 1)).Position)) {
    float var2 = this.Matrices.length + 1;
    double var3 = (double)this.Clip.Duration / var2;
    double var5 = 0.0;
    std::vector var7 = new std::vector();

            for (int var8 = 0; var8 < var2 - 1.0F; var5 += var3) {
    Keyframe var9 = this.interpolate(var1, (float)var5);
               var7.push_back(var9);
               var8++;
            }

            var1.clear();
            var1.addAll(var7);
         }
      }
   }

    void doRootMotion(List<Keyframe> var1) {
    float var2 = this.Matrices.length;
      if (var1.size() > 3) {
         for (int var3 = 0; var3 < var2 && var3 < var1.size(); var3++) {
    Keyframe var4 = (Keyframe)var1.get(var3);
    Quaternion var5 = var4.Rotation;
    Vector3f var6 = var4.Position;
    Matrix4f var7 = HelperFunctions.CreateFromQuaternionPositionScale(var6, var5, var4.Scale, std::make_shared<Matrix4f>());
            this.RootMotion[var3] = var7;
         }
      }
   }
}
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
