#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/skinnedmodel/model/ModelLoader/LoadMode.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {


// $VF: synthetic class
class ModelLoader {
public:
   static {
      try {
         $SwitchMap$zombie$core$skinnedmodel$model$ModelLoader$LoadMode[LoadMode.Version.ordinal()] = 1;
      } catch (NoSuchFieldError var14) {
      }

      try {
         $SwitchMap$zombie$core$skinnedmodel$model$ModelLoader$LoadMode[LoadMode.ModelName.ordinal()] = 2;
      } catch (NoSuchFieldError var13) {
      }

      try {
         $SwitchMap$zombie$core$skinnedmodel$model$ModelLoader$LoadMode[LoadMode.VertexStrideElementCount.ordinal()] = 3;
      } catch (NoSuchFieldError var12) {
      }

      try {
         $SwitchMap$zombie$core$skinnedmodel$model$ModelLoader$LoadMode[LoadMode.VertexCount.ordinal()] = 4;
      } catch (NoSuchFieldError var11) {
      }

      try {
         $SwitchMap$zombie$core$skinnedmodel$model$ModelLoader$LoadMode[LoadMode.VertexBuffer.ordinal()] = 5;
      } catch (NoSuchFieldError var10) {
      }

      try {
         $SwitchMap$zombie$core$skinnedmodel$model$ModelLoader$LoadMode[LoadMode.NumberOfFaces.ordinal()] = 6;
      } catch (NoSuchFieldError var9) {
      }

      try {
         $SwitchMap$zombie$core$skinnedmodel$model$ModelLoader$LoadMode[LoadMode.FaceData.ordinal()] = 7;
      } catch (NoSuchFieldError var8) {
      }

      try {
         $SwitchMap$zombie$core$skinnedmodel$model$ModelLoader$LoadMode[LoadMode.NumberOfBones.ordinal()] = 8;
      } catch (NoSuchFieldError var7) {
      }

      try {
         $SwitchMap$zombie$core$skinnedmodel$model$ModelLoader$LoadMode[LoadMode.SkeletonHierarchy.ordinal()] = 9;
      } catch (NoSuchFieldError var6) {
      }

      try {
         $SwitchMap$zombie$core$skinnedmodel$model$ModelLoader$LoadMode[LoadMode.BindPose.ordinal()] = 10;
      } catch (NoSuchFieldError var5) {
      }

      try {
         $SwitchMap$zombie$core$skinnedmodel$model$ModelLoader$LoadMode[LoadMode.InvBindPose.ordinal()] = 11;
      } catch (NoSuchFieldError var4) {
      }

      try {
         $SwitchMap$zombie$core$skinnedmodel$model$ModelLoader$LoadMode[LoadMode.SkinOffsetMatrices.ordinal()] = 12;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$zombie$core$skinnedmodel$model$ModelLoader$LoadMode[LoadMode.NumberOfAnims.ordinal()] = 13;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$zombie$core$skinnedmodel$model$ModelLoader$LoadMode[LoadMode.Anim.ordinal()] = 14;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
