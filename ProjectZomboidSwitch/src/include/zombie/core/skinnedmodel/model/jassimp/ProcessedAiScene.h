#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "jassimp/AiBuiltInWrapperProvider.h"
#include "jassimp/AiMatrix4f.h"
#include "jassimp/AiMesh.h"
#include "jassimp/AiNode.h"
#include "jassimp/AiScene.h"
#include "org/lwjgl/util/vector/Matrix4f.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/core/skinnedmodel/animation/AnimationClip.h"
#include "zombie/core/skinnedmodel/animation/Keyframe.h"
#include "zombie/core/skinnedmodel/model/AnimationAsset.h"
#include "zombie/core/skinnedmodel/model/ModelMesh.h"
#include "zombie/core/skinnedmodel/model/SkinningData.h"
#include "zombie/core/skinnedmodel/model/VertexBufferObject.h"
#include "zombie/core/skinnedmodel/model/VertexBufferObject/VertexArray.h"
#include "zombie/core/skinnedmodel/model/jassimp/JAssImpImporter/LoadMode.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/util/StringUtils.h"
#include <algorithm>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {
namespace jassimp {


class ProcessedAiScene {
public:
    ImportedSkeleton skeleton;
    ImportedSkinnedMesh skinnedMesh;
    ImportedStaticMesh staticMesh;
    Matrix4f transform = nullptr;

    private ProcessedAiScene() {
   }

    static ProcessedAiScene process(ProcessedAiSceneParams var0) {
    ProcessedAiScene var1 = std::make_shared<ProcessedAiScene>();
      var1.processAiScene(var0);
    return var1;
   }

    void processAiScene(ProcessedAiSceneParams var1) {
    AiScene var2 = var1.scene;
    LoadMode var3 = var1.mode;
    std::string var4 = var1.meshName;
    AiMesh var5 = this.findMesh(var2, var4);
      if (var5 == nullptr) {
         DebugLog.General.error("No such mesh \"%s\"", new Object[]{var4});
      } else {
         if (var3 != LoadMode.StaticMesh && var5.hasBones()) {
    ImportedSkeletonParams var6 = ImportedSkeletonParams.create(var1, var5);
            this.skeleton = ImportedSkeleton.process(var6);
            if (var3 != LoadMode.AnimationOnly) {
               this.skinnedMesh = std::make_shared<ImportedSkinnedMesh>(this.skeleton, var5);
            }
         } else {
            this.staticMesh = std::make_shared<ImportedStaticMesh>(var5);
         }

         if (this.staticMesh != nullptr || this.skinnedMesh != nullptr) {
    AiBuiltInWrapperProvider var11 = std::make_shared<AiBuiltInWrapperProvider>();
    AiNode var7 = (AiNode)var2.getSceneRoot(var11);
    AiNode var8 = this.findParentNodeForMesh(var2.getMeshes().indexOf(var5), var7);
            if (var8 != nullptr) {
               this.transform = JAssImpImporter.getMatrixFromAiMatrix((AiMatrix4f)var8.getTransform(var11));

               for (AiNode var9 = var8.getParent(); var9 != nullptr; var9 = var9.getParent()) {
    Matrix4f var10 = JAssImpImporter.getMatrixFromAiMatrix((AiMatrix4f)var9.getTransform(var11));
                  Matrix4f.mul(var10, this.transform, this.transform);
               }
            }
         }
      }
   }

    AiMesh findMesh(AiScene var1, const std::string& var2) {
      if (var1.getNumMeshes() == 0) {
    return nullptr;
      } else if (StringUtils.isNullOrWhitespace(var2)) {
         for (AiMesh var10 : var1.getMeshes()) {
            if (var10.hasBones()) {
    return var10;
            }
         }

         return (AiMesh)var1.getMeshes().get(0);
      } else {
         for (AiMesh var4 : var1.getMeshes()) {
            if (var4.getName().equalsIgnoreCase(var2)) {
    return var4;
            }
         }

    AiBuiltInWrapperProvider var7 = std::make_shared<AiBuiltInWrapperProvider>();
    AiNode var9 = (AiNode)var1.getSceneRoot(var7);
    AiNode var5 = JAssImpImporter.FindNode(var2, var9);
         if (var5 != nullptr && var5.getNumMeshes() == 1) {
    int var6 = var5.getMeshes()[0];
            return (AiMesh)var1.getMeshes().get(var6);
         } else {
    return nullptr;
         }
      }
   }

    AiNode findParentNodeForMesh(int var1, AiNode var2) {
      for (int var3 = 0; var3 < var2.getNumMeshes(); var3++) {
         if (var2.getMeshes()[var3] == var1) {
    return var2;
         }
      }

      for (AiNode var4 : var2.getChildren()) {
    AiNode var5 = this.findParentNodeForMesh(var1, var4);
         if (var5 != nullptr) {
    return var5;
         }
      }

    return nullptr;
   }

    void applyToMesh(ModelMesh var1, LoadMode var2, bool var3, SkinningData var4) {
      var1.m_transform = nullptr;
      if (this.transform != nullptr) {
         var1.m_transform = PZMath.convertMatrix(this.transform, new org.joml.Matrix4f());
      }

      if (this.staticMesh != nullptr && !ModelManager.NoOpenGL) {
         var1.minXYZ.set(this.staticMesh.minXYZ);
         var1.maxXYZ.set(this.staticMesh.maxXYZ);
         var1.m_bHasVBO = true;
    VertexArray var5 = this.staticMesh.verticesUnskinned;
         int[] var6 = this.staticMesh.elements;
         RenderThread.queueInvokeOnRenderContext(() -> {
            var1.SetVertexBuffer(std::make_shared<VertexBufferObject>(var5, var6));
            if (ModelManager.instance.bCreateSoftwareMeshes) {
               var1.softwareMesh.vb = var1.vb;
            }
         });
      }

      if (var1.skinningData != nullptr) {
         if (var4 == nullptr || var1.skinningData.AnimationClips != var4.AnimationClips) {
            var1.skinningData.AnimationClips.clear();
         }

         var1.skinningData.InverseBindPose.clear();
         var1.skinningData.BindPose.clear();
         var1.skinningData.BoneOffset.clear();
         var1.skinningData.BoneIndices.clear();
         var1.skinningData.SkeletonHierarchy.clear();
         var1.skinningData = nullptr;
      }

      if (this.skeleton != nullptr) {
    ImportedSkeleton var7 = this.skeleton;
    std::unordered_map var9 = var7.clips;
         if (var4 != nullptr) {
            var7.clips.clear();
            var9 = var4.AnimationClips;
         }

         JAssImpImporter.replaceHashMapKeys(var7.boneIndices, "SkinningData.boneIndices");
         var1.skinningData = std::make_shared<SkinningData>(var9, var7.bindPose, var7.invBindPose, var7.skinOffsetMatrices, var7.SkeletonHierarchy, var7.boneIndices);
      }

      if (this.skinnedMesh != nullptr && !ModelManager.NoOpenGL) {
         var1.m_bHasVBO = true;
    VertexArray var8 = this.skinnedMesh.vertices;
         int[] var10 = this.skinnedMesh.elements;
         RenderThread.queueInvokeOnRenderContext(() -> {
            var1.SetVertexBuffer(std::make_shared<VertexBufferObject>(var8, var10, var3));
            if (ModelManager.instance.bCreateSoftwareMeshes) {
               var1.softwareMesh.vb = var1.vb;
            }
         });
      }

      this.skeleton = nullptr;
      this.skinnedMesh = nullptr;
      this.staticMesh = nullptr;
   }

    void applyToAnimation(AnimationAsset var1) {
      for (Entry var3 : this.skeleton.clips.entrySet()) {
         for (Keyframe var7 : ((AnimationClip)var3.getValue()).getKeyframes()) {
            var7.BoneName = JAssImpImporter.getSharedString(var7.BoneName, "Keyframe.BoneName");
         }
      }

      var1.AnimationClips = this.skeleton.clips;
      this.skeleton = nullptr;
   }
}
} // namespace jassimp
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
