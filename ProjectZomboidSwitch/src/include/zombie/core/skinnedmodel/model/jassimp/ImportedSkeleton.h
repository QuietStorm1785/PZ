#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/list/array/TFloatArrayList.h"
#include "jassimp/AiAnimation.h"
#include "jassimp/AiBone.h"
#include "jassimp/AiBuiltInWrapperProvider.h"
#include "jassimp/AiMatrix4f.h"
#include "jassimp/AiMesh.h"
#include "jassimp/AiNode.h"
#include "jassimp/AiNodeAnim.h"
#include "jassimp/AiQuaternion.h"
#include "jassimp/AiScene.h"
#include "org/lwjgl/util/vector/Matrix4f.h"
#include "org/lwjgl/util/vector/Quaternion.h"
#include "org/lwjgl/util/vector/Vector3f.h"
#include "zombie/core/skinnedmodel/HelperFunctions.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/core/skinnedmodel/animation/AnimationClip.h"
#include "zombie/core/skinnedmodel/animation/Keyframe.h"
#include "zombie/core/skinnedmodel/animation/StaticAnimation.h"
#include "zombie/core/skinnedmodel/model/SkinningData.h"
#include "zombie/core/skinnedmodel/model/jassimp/JAssImpImporter/LoadMode.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/util/StringUtils.h"
#include <algorithm>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {
namespace jassimp {


class ImportedSkeleton {
public:
   const std::unordered_map<std::string, int> boneIndices = std::make_unique<std::unordered_map<>>();
   const std::vector<int> SkeletonHierarchy = std::make_unique<std::vector<>>();
   const std::vector<Matrix4f> bindPose = std::make_unique<std::vector<>>();
   const std::vector<Matrix4f> invBindPose = std::make_unique<std::vector<>>();
   const std::vector<Matrix4f> skinOffsetMatrices = std::make_unique<std::vector<>>();
    AiNode rootBoneNode = nullptr;
   const std::unordered_map<std::string, AnimationClip> clips = std::make_unique<std::unordered_map<>>();
    const AiBuiltInWrapperProvider wrapper = std::make_shared<AiBuiltInWrapperProvider>();
    const Quaternion end = std::make_shared<Quaternion>();

    private ImportedSkeleton() {
   }

    static ImportedSkeleton process(ImportedSkeletonParams var0) {
    ImportedSkeleton var1 = std::make_shared<ImportedSkeleton>();
      var1.processAiScene(var0);
    return var1;
   }

    void processAiScene(ImportedSkeletonParams var1) {
    AiScene var2 = var1.scene;
    LoadMode var3 = var1.mode;
    SkinningData var4 = var1.skinnedTo;
    float var5 = var1.animBonesScaleModifier;
    Quaternion var6 = var1.animBonesRotateModifier;
    AiMesh var7 = var1.mesh;
    AiNode var8 = (AiNode)var2.getSceneRoot(this.wrapper);
      this.rootBoneNode = JAssImpImporter.FindNode("Dummy01", var8);
    bool var9;
      if (this.rootBoneNode == nullptr) {
         this.rootBoneNode = JAssImpImporter.FindNode("VehicleSkeleton", var8);
         var9 = true;
      } else {
         var9 = false;
      }

      while (this.rootBoneNode != nullptr && this.rootBoneNode.getParent() != nullptr && this.rootBoneNode.getParent() != var8) {
         this.rootBoneNode = this.rootBoneNode.getParent();
      }

      if (this.rootBoneNode == nullptr) {
         this.rootBoneNode = var8;
      }

    std::vector var10 = new std::vector();
      JAssImpImporter.CollectBoneNodes(var10, this.rootBoneNode);
    AiNode var11 = JAssImpImporter.FindNode("Translation_Data", var8);
      if (var11 != nullptr) {
         var10.push_back(var11);

         for (AiNode var12 = var11.getParent(); var12 != nullptr && var12 != var8; var12 = var12.getParent()) {
            var10.push_back(var12);
         }
      }

      if (var4 != nullptr) {
         this.boneIndices.putAll(var4.BoneIndices);
         this.SkeletonHierarchy.addAll(var4.SkeletonHierarchy);
      }

      for (int var27 = 0; var27 < var10.size(); var27++) {
    AiNode var13 = (AiNode)var10.get(var27);
    std::string var14 = var13.getName();
         if (!this.boneIndices.containsKey(var14)) {
    int var15 = this.boneIndices.size();
            this.boneIndices.put(var14, var15);
            if (var13 == this.rootBoneNode) {
               this.SkeletonHierarchy.push_back(-1);
            } else {
    AiNode var16 = var13.getParent();

               while (var16 != nullptr && !this.boneIndices.containsKey(var16.getName())) {
                  var16 = var16.getParent();
               }

               if (var16 != nullptr) {
                  this.SkeletonHierarchy.push_back(this.boneIndices.get(var16.getName()));
               } else {
                  this.SkeletonHierarchy.push_back(0);
               }
            }
         }
      }

    Matrix4f var28 = std::make_shared<Matrix4f>();

      for (int var29 = 0; var29 < this.boneIndices.size(); var29++) {
         this.bindPose.push_back(var28);
         this.skinOffsetMatrices.push_back(var28);
      }

    std::vector var30 = var7.getBones();

      for (int var31 = 0; var31 < var10.size(); var31++) {
    AiNode var33 = (AiNode)var10.get(var31);
    std::string var36 = var33.getName();
    AiBone var17 = JAssImpImporter.FindAiBone(var36, var30);
         if (var17 != nullptr) {
    AiMatrix4f var18 = (AiMatrix4f)var17.getOffsetMatrix(this.wrapper);
            if (var18 != nullptr) {
    Matrix4f var19 = JAssImpImporter.getMatrixFromAiMatrix(var18);
    Matrix4f var20 = std::make_shared<Matrix4f>(var19);
               var20.invert();
    Matrix4f var21 = std::make_shared<Matrix4f>();
               var21.setIdentity();
    std::string var22 = var33.getParent().getName();
    AiBone var23 = JAssImpImporter.FindAiBone(var22, var30);
               if (var23 != nullptr) {
    AiMatrix4f var24 = (AiMatrix4f)var23.getOffsetMatrix(this.wrapper);
                  if (var24 != nullptr) {
                     JAssImpImporter.getMatrixFromAiMatrix(var24, var21);
                  }
               }

    Matrix4f var41 = std::make_shared<Matrix4f>(var21);
               var41.invert();
    Matrix4f var25 = std::make_shared<Matrix4f>();
               Matrix4f.mul(var20, var41, var25);
               var25.invert();
    int var26 = this.boneIndices.get(var36);
               this.bindPose.set(var26, var25);
               this.skinOffsetMatrices.set(var26, var19);
            }
         }
      }

    int var32 = this.bindPose.size();

      for (int var34 = 0; var34 < var32; var34++) {
    Matrix4f var37 = std::make_shared<Matrix4f>(this.bindPose.get(var34));
         var37.invert();
         this.invBindPose.push_back(var34, var37);
      }

      if (var3 == LoadMode.AnimationOnly || var4 == nullptr) {
    int var35 = var2.getNumAnimations();
         if (var35 > 0) {
    std::vector var38 = var2.getAnimations();

            for (int var39 = 0; var39 < var35; var39++) {
    AiAnimation var40 = (AiAnimation)var38.get(var39);
               if (var9) {
                  this.processAnimation(var40, var9, 1.0F, nullptr);
               } else {
                  this.processAnimation(var40, var9, var5, var6);
               }
            }
         }
      }
   }

    void processAnimationOld(AiAnimation var1, bool var2) {
    std::vector var3 = new std::vector();
    float var4 = (float)var1.getDuration();
    float var5 = var4 / (float)var1.getTicksPerSecond();
    std::vector var6 = new std::vector();
    std::vector var7 = var1.getChannels();

      for (int var8 = 0; var8 < var7.size(); var8++) {
    AiNodeAnim var9 = (AiNodeAnim)var7.get(var8);

         for (int var10 = 0; var10 < var9.getNumPosKeys(); var10++) {
    float var11 = (float)var9.getPosKeyTime(var10);
            if (!var6.contains(var11)) {
               var6.push_back(var11);
            }
         }

         for (int var17 = 0; var17 < var9.getNumRotKeys(); var17++) {
    float var21 = (float)var9.getRotKeyTime(var17);
            if (!var6.contains(var21)) {
               var6.push_back(var21);
            }
         }

         for (int var18 = 0; var18 < var9.getNumScaleKeys(); var18++) {
    float var22 = (float)var9.getScaleKeyTime(var18);
            if (!var6.contains(var22)) {
               var6.push_back(var22);
            }
         }
      }

      Collections.sort(var6);

      for (int var13 = 0; var13 < var6.size(); var13++) {
         for (int var15 = 0; var15 < var7.size(); var15++) {
    AiNodeAnim var19 = (AiNodeAnim)var7.get(var15);
    Keyframe var23 = std::make_shared<Keyframe>();
            var23.clear();
            var23.BoneName = var19.getNodeName();
    int var12 = this.boneIndices.get(var23.BoneName);
            if (var12 == nullptr) {
               DebugLog.General.error("Could not find bone index for node name: \"%s\"", new Object[]{var23.BoneName});
            } else {
               var23.Bone = var12;
               var23.Time = (float)var6.get(var13) / (float)var1.getTicksPerSecond();
               if (!var2) {
                  var23.Position = JAssImpImporter.GetKeyFramePosition(var19, (float)var6.get(var13));
                  var23.Rotation = JAssImpImporter.GetKeyFrameRotation(var19, (float)var6.get(var13));
                  var23.Scale = JAssImpImporter.GetKeyFrameScale(var19, (float)var6.get(var13));
               } else {
                  var23.Position = this.GetKeyFramePosition(var19, (float)var6.get(var13), var1.getDuration());
                  var23.Rotation = this.GetKeyFrameRotation(var19, (float)var6.get(var13), var1.getDuration());
                  var23.Scale = this.GetKeyFrameScale(var19, (float)var6.get(var13), var1.getDuration());
               }

               if (var23.Bone >= 0) {
                  var3.push_back(var23);
               }
            }
         }
      }

    std::string var14 = var1.getName();
    int var16 = var14.indexOf(124);
      if (var16 > 0) {
         var14 = var14.substr(var16 + 1);
      }

    AnimationClip var20 = std::make_shared<AnimationClip>(var5, var3, var14, true);
      var3.clear();
      if (ModelManager.instance.bCreateSoftwareMeshes) {
         var20.staticClip = std::make_shared<StaticAnimation>(var20);
      }

      this.clips.put(var14, var20);
   }

    void processAnimation(AiAnimation var1, bool var2, float var3, Quaternion var4) {
    std::vector var5 = new std::vector();
    float var6 = (float)var1.getDuration();
    float var7 = var6 / (float)var1.getTicksPerSecond();
      TFloatArrayList[] var8 = new TFloatArrayList[this.boneIndices.size()];
      Arrays.fill(var8, nullptr);
    std::vector var9 = new std::vector(this.boneIndices.size());

      for (int var10 = 0; var10 < this.boneIndices.size(); var10++) {
         var9.push_back(nullptr);
      }

      this.collectBoneFrames(var1, var8, var9);
    Quaternion var24 = nullptr;
    bool var11 = var4 != nullptr;
      if (var11) {
         var24 = std::make_unique<Quaternion>();
         Quaternion.mulInverse(var24, var4, var24);
      }

      for (int var12 = 0; var12 < this.boneIndices.size(); var12++) {
    std::vector var13 = (std::vector)var9.get(var12);
         if (var13 == nullptr) {
            if (var12 == 0 && var4 != nullptr) {
    Quaternion var28 = std::make_shared<Quaternion>();
               var28.set(var4);
               this.addDefaultAnimTrack("RootNode", var12, var28, std::make_shared<Vector3f>(0.0F, 0.0F, 0.0F), var5, var7);
            }
         } else {
    TFloatArrayList var14 = var8[var12];
            if (var14 != nullptr) {
               var14.sort();
    int var15 = this.getParentBoneIdx(var12);
    bool var16 = var11 && (var15 == 0 || this.doesParentBoneHaveAnimFrames(var8, var9, var12));

               for (int var17 = 0; var17 < var14.size(); var17++) {
    float var18 = var14.get(var17);
    float var19 = var18 / (float)var1.getTicksPerSecond();

                  for (int var20 = 0; var20 < var13.size(); var20++) {
    AiNodeAnim var21 = (AiNodeAnim)var13.get(var20);
    Keyframe var22 = std::make_shared<Keyframe>();
                     var22.clear();
                     var22.BoneName = var21.getNodeName();
                     var22.Bone = var12;
                     var22.Time = var19;
                     if (!var2) {
                        var22.Position = JAssImpImporter.GetKeyFramePosition(var21, var18);
                        var22.Rotation = JAssImpImporter.GetKeyFrameRotation(var21, var18);
                        var22.Scale = JAssImpImporter.GetKeyFrameScale(var21, var18);
                     } else {
                        var22.Position = this.GetKeyFramePosition(var21, var18, var6);
                        var22.Rotation = this.GetKeyFrameRotation(var21, var18, var6);
                        var22.Scale = this.GetKeyFrameScale(var21, var18, var6);
                     }

                     var22.Position.x *= var3;
                     var22.Position.y *= var3;
                     var22.Position.z *= var3;
                     if (var11) {
                        if (var16) {
                           Quaternion.mul(var24, var22.Rotation, var22.Rotation);
    bool var23 = StringUtils.startsWithIgnoreCase(var22.BoneName, "Translation_Data");
                           if (!var23) {
                              HelperFunctions.transform(var24, var22.Position, var22.Position);
                           }
                        }

                        Quaternion.mul(var22.Rotation, var4, var22.Rotation);
                     }

                     var5.push_back(var22);
                  }
               }
            }
         }
      }

    std::string var25 = var1.getName();
    int var27 = var25.indexOf(124);
      if (var27 > 0) {
         var25 = var25.substr(var27 + 1);
      }

      var25 = var25.trim();
    AnimationClip var29 = std::make_shared<AnimationClip>(var7, var5, var25, true);
      var5.clear();
      if (ModelManager.instance.bCreateSoftwareMeshes) {
         var29.staticClip = std::make_shared<StaticAnimation>(var29);
      }

      this.clips.put(var25, var29);
   }

    void addDefaultAnimTrack(const std::string& var1, int var2, Quaternion var3, Vector3f var4, std::vector<Keyframe> var5, float var6) {
    Vector3f var7 = std::make_shared<Vector3f>(1.0F, 1.0F, 1.0F);
    Keyframe var8 = std::make_shared<Keyframe>();
      var8.clear();
      var8.BoneName = var1;
      var8.Bone = var2;
      var8.Time = 0.0F;
      var8.Position = var4;
      var8.Rotation = var3;
      var8.Scale = var7;
      var5.push_back(var8);
    Keyframe var9 = std::make_shared<Keyframe>();
      var9.clear();
      var9.BoneName = var1;
      var9.Bone = var2;
      var9.Time = var6;
      var9.Position = var4;
      var9.Rotation = var3;
      var9.Scale = var7;
      var5.push_back(var9);
   }

    bool doesParentBoneHaveAnimFrames(TFloatArrayList[] var1, std::vector<std::vector<AiNodeAnim>> var2, int var3) {
    int var4 = this.getParentBoneIdx(var3);
      return var4 < 0 ? false : this.doesBoneHaveAnimFrames(var1, var2, var4);
   }

    bool doesBoneHaveAnimFrames(TFloatArrayList[] var1, std::vector<std::vector<AiNodeAnim>> var2, int var3) {
    TFloatArrayList var4 = var1[var3];
      if (var4 != nullptr && var4.size() > 0) {
    std::vector var5 = (std::vector)var2.get(var3);
         return var5.size() > 0;
      } else {
    return false;
      }
   }

    void collectBoneFrames(AiAnimation var1, TFloatArrayList[] var2, std::vector<std::vector<AiNodeAnim>> var3) {
    std::vector var4 = var1.getChannels();

      for (int var5 = 0; var5 < var4.size(); var5++) {
    AiNodeAnim var6 = (AiNodeAnim)var4.get(var5);
    std::string var7 = var6.getNodeName();
    int var8 = this.boneIndices.get(var7);
         if (var8 == nullptr) {
            DebugLog.General.error("Could not find bone index for node name: \"%s\"", new Object[]{var7});
         } else {
    std::vector var9 = (std::vector)var3.get(var8);
            if (var9 == nullptr) {
               var9 = std::make_unique<std::vector>();
               var3.set(var8, var9);
            }

            var9.push_back(var6);
    TFloatArrayList var10 = var2[var8];
            if (var10 == nullptr) {
               var10 = std::make_unique<TFloatArrayList>();
               var2[var8] = var10;
            }

            for (int var11 = 0; var11 < var6.getNumPosKeys(); var11++) {
    float var12 = (float)var6.getPosKeyTime(var11);
               if (!var10.contains(var12)) {
                  var10.push_back(var12);
               }
            }

            for (int var13 = 0; var13 < var6.getNumRotKeys(); var13++) {
    float var15 = (float)var6.getRotKeyTime(var13);
               if (!var10.contains(var15)) {
                  var10.push_back(var15);
               }
            }

            for (int var14 = 0; var14 < var6.getNumScaleKeys(); var14++) {
    float var16 = (float)var6.getScaleKeyTime(var14);
               if (!var10.contains(var16)) {
                  var10.push_back(var16);
               }
            }
         }
      }
   }

    int getParentBoneIdx(int var1) {
      return var1 > -1 ? this.SkeletonHierarchy.get(var1) : -1;
   }

    int getNumBoneAncestors(int var1) {
    int var2 = 0;

      for (int var3 = this.getParentBoneIdx(var1); var3 > -1; var3 = this.getParentBoneIdx(var3)) {
         var2++;
      }

    return var2;
   }

    Vector3f GetKeyFramePosition(AiNodeAnim var1, float var2, double var3) {
    Vector3f var5 = std::make_shared<Vector3f>();
      if (var1.getNumPosKeys() == 0) {
    return var5;
      } else {
    int var6 = 0;

         while (var6 < var1.getNumPosKeys() - 1 && !(var2 < var1.getPosKeyTime(var6 + 1))) {
            var6++;
         }

    int var7 = (var6 + 1) % var1.getNumPosKeys();
    float var8 = (float)var1.getPosKeyTime(var6);
    float var9 = (float)var1.getPosKeyTime(var7);
    float var10 = var9 - var8;
         if (var10 < 0.0F) {
            var10 = (float)(var10 + var3);
         }

         if (var10 > 0.0F) {
    float var11 = var9 - var8;
    float var12 = var2 - var8;
            var12 /= var11;
    float var13 = var1.getPosKeyX(var6);
    float var14 = var1.getPosKeyX(var7);
    float var15 = var13 + var12 * (var14 - var13);
    float var16 = var1.getPosKeyY(var6);
    float var17 = var1.getPosKeyY(var7);
    float var18 = var16 + var12 * (var17 - var16);
    float var19 = var1.getPosKeyZ(var6);
    float var20 = var1.getPosKeyZ(var7);
    float var21 = var19 + var12 * (var20 - var19);
            var5.set(var15, var18, var21);
         } else {
            var5.set(var1.getPosKeyX(var6), var1.getPosKeyY(var6), var1.getPosKeyZ(var6));
         }

    return var5;
      }
   }

    Quaternion GetKeyFrameRotation(AiNodeAnim var1, float var2, double var3) {
    Quaternion var5 = std::make_shared<Quaternion>();
      if (var1.getNumRotKeys() == 0) {
    return var5;
      } else {
    int var6 = 0;

         while (var6 < var1.getNumRotKeys() - 1 && !(var2 < var1.getRotKeyTime(var6 + 1))) {
            var6++;
         }

    int var7 = (var6 + 1) % var1.getNumRotKeys();
    float var8 = (float)var1.getRotKeyTime(var6);
    float var9 = (float)var1.getRotKeyTime(var7);
    float var10 = var9 - var8;
         if (var10 < 0.0F) {
            var10 = (float)(var10 + var3);
         }

         if (var10 > 0.0F) {
    float var11 = (var2 - var8) / var10;
    AiQuaternion var12 = (AiQuaternion)var1.getRotKeyQuaternion(var6, this.wrapper);
    AiQuaternion var13 = (AiQuaternion)var1.getRotKeyQuaternion(var7, this.wrapper);
    double var14 = var12.getX() * var13.getX() + var12.getY() * var13.getY() + var12.getZ() * var13.getZ() + var12.getW() * var13.getW();
            this.end.set(var13.getX(), var13.getY(), var13.getZ(), var13.getW());
            if (var14 < 0.0) {
               var14 *= -1.0;
               this.end.setX(-this.end.getX());
               this.end.setY(-this.end.getY());
               this.end.setZ(-this.end.getZ());
               this.end.setW(-this.end.getW());
            }

    double var16;
    double var18;
            if (1.0 - var14 > 1.0E-4) {
    double var20 = Math.acos(var14);
    double var22 = Math.sin(var20);
               var16 = Math.sin((1.0 - var11) * var20) / var22;
               var18 = Math.sin(var11 * var20) / var22;
            } else {
               var16 = 1.0 - var11;
               var18 = var11;
            }

            var5.set(
               (float)(var16 * var12.getX() + var18 * this.end.getX()),
               (float)(var16 * var12.getY() + var18 * this.end.getY()),
               (float)(var16 * var12.getZ() + var18 * this.end.getZ()),
               (float)(var16 * var12.getW() + var18 * this.end.getW())
            );
         } else {
    float var24 = var1.getRotKeyX(var6);
    float var25 = var1.getRotKeyY(var6);
    float var26 = var1.getRotKeyZ(var6);
    float var27 = var1.getRotKeyW(var6);
            var5.set(var24, var25, var26, var27);
         }

    return var5;
      }
   }

    Vector3f GetKeyFrameScale(AiNodeAnim var1, float var2, double var3) {
    Vector3f var5 = std::make_shared<Vector3f>(1.0F, 1.0F, 1.0F);
      if (var1.getNumScaleKeys() == 0) {
    return var5;
      } else {
    int var6 = 0;

         while (var6 < var1.getNumScaleKeys() - 1 && !(var2 < var1.getScaleKeyTime(var6 + 1))) {
            var6++;
         }

         var5.set(var1.getScaleKeyX(var6), var1.getScaleKeyY(var6), var1.getScaleKeyZ(var6));
    return var5;
      }
   }
}
} // namespace jassimp
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
