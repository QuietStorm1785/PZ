#pragma once
#include "jassimp/AiBuiltInWrapperProvider.h"
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
#include "zombie/debug/DebugLog.h"
#include "zombie/util/StringUtils.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {
namespace jassimp {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ProcessedAiScene {
public:
  ImportedSkeleton skeleton;
  ImportedSkinnedMesh skinnedMesh;
  ImportedStaticMesh staticMesh;
  Matrix4f transform = null;

private
  ProcessedAiScene() {}

  static ProcessedAiScene
  process(ProcessedAiSceneParams processedAiSceneParams) {
    ProcessedAiScene processedAiScene = new ProcessedAiScene();
    processedAiScene.processAiScene(processedAiSceneParams);
    return processedAiScene;
  }

  void processAiScene(ProcessedAiSceneParams processedAiSceneParams) {
    AiScene aiScene = processedAiSceneParams.scene;
    JAssImpImporter.LoadMode loadMode = processedAiSceneParams.mode;
    std::string string = processedAiSceneParams.meshName;
    AiMesh aiMesh = this.findMesh(aiScene, string);
    if (aiMesh == nullptr) {
      DebugLog.General.error("No such mesh \"%s\"", string);
    } else {
      if (loadMode != JAssImpImporter.LoadMode.StaticMesh &&
          aiMesh.hasBones()) {
        ImportedSkeletonParams importedSkeletonParams =
            ImportedSkeletonParams.create(processedAiSceneParams, aiMesh);
        this.skeleton = ImportedSkeleton.process(importedSkeletonParams);
        if (loadMode != JAssImpImporter.LoadMode.AnimationOnly) {
          this.skinnedMesh = new ImportedSkinnedMesh(this.skeleton, aiMesh);
        }
      } else {
        this.staticMesh = new ImportedStaticMesh(aiMesh);
      }

      if (this.staticMesh != nullptr || this.skinnedMesh != nullptr) {
        AiBuiltInWrapperProvider aiBuiltInWrapperProvider =
            new AiBuiltInWrapperProvider();
        AiNode aiNode0 = aiScene.getSceneRoot(aiBuiltInWrapperProvider);
        AiNode aiNode1 = this.findParentNodeForMesh(
            aiScene.getMeshes().indexOf(aiMesh), aiNode0);
        if (aiNode1 != nullptr) {
          this.transform = JAssImpImporter.getMatrixFromAiMatrix(
              aiNode1.getTransform(aiBuiltInWrapperProvider));

          for (AiNode aiNode2 = aiNode1.getParent(); aiNode2 != nullptr;
               aiNode2 = aiNode2.getParent()) {
            Matrix4f matrix4f = JAssImpImporter.getMatrixFromAiMatrix(
                aiNode2.getTransform(aiBuiltInWrapperProvider));
            Matrix4f.mul(matrix4f, this.transform, this.transform);
          }
        }
      }
    }
  }

  AiMesh findMesh(AiScene aiScene, const std::string &string) {
    if (aiScene.getNumMeshes() == 0) {
      return null;
    } else if (StringUtils.isNullOrWhitespace(string)) {
      for (AiMesh aiMesh0 : aiScene.getMeshes()) {
        if (aiMesh0.hasBones()) {
          return aiMesh0;
        }
      }

      return aiScene.getMeshes().get(0);
    } else {
      for (AiMesh aiMesh1 : aiScene.getMeshes()) {
        if (aiMesh1.getName().equalsIgnoreCase(string)) {
          return aiMesh1;
        }
      }

      AiBuiltInWrapperProvider aiBuiltInWrapperProvider =
          new AiBuiltInWrapperProvider();
      AiNode aiNode0 = aiScene.getSceneRoot(aiBuiltInWrapperProvider);
      AiNode aiNode1 = JAssImpImporter.FindNode(string, aiNode0);
      if (aiNode1 != nullptr && aiNode1.getNumMeshes() == 1) {
        int int0 = aiNode1.getMeshes()[0];
        return aiScene.getMeshes().get(int0);
      } else {
        return null;
      }
    }
  }

  AiNode findParentNodeForMesh(int int1, AiNode aiNode0) {
    for (int int0 = 0; int0 < aiNode0.getNumMeshes(); int0++) {
      if (aiNode0.getMeshes()[int0] == int1) {
        return aiNode0;
      }
    }

    for (AiNode aiNode1 : aiNode0.getChildren()) {
      AiNode aiNode2 = this.findParentNodeForMesh(int1, aiNode1);
      if (aiNode2 != nullptr) {
        return aiNode2;
      }
    }

    return null;
  }

  void applyToMesh(ModelMesh modelMesh, JAssImpImporter.LoadMode var2,
                   bool boolean0, SkinningData skinningData) {
    modelMesh.m_transform = nullptr;
    if (this.transform != nullptr) {
      modelMesh.m_transform =
          PZMath.convertMatrix(this.transform, new org.joml.Matrix4f());
    }

    if (this.staticMesh != nullptr && !ModelManager.NoOpenGL) {
      modelMesh.minXYZ.set(this.staticMesh.minXYZ);
      modelMesh.maxXYZ.set(this.staticMesh.maxXYZ);
      modelMesh.m_bHasVBO = true;
      VertexBufferObject.VertexArray vertexArray0 =
          this.staticMesh.verticesUnskinned;
      int[] ints0 = this.staticMesh.elements;
      RenderThread.queueInvokeOnRenderContext(()->{
        modelMesh.SetVertexBuffer(new VertexBufferObject(vertexArray0, ints0));
        if (ModelManager.instance.bCreateSoftwareMeshes) {
          modelMesh.softwareMesh.vb = modelMesh.vb;
        }
      });
    }

    if (modelMesh.skinningData != nullptr) {
      if (skinningData == nullptr || modelMesh.skinningData.AnimationClips !=
                                         skinningData.AnimationClips) {
        modelMesh.skinningData.AnimationClips.clear();
      }

      modelMesh.skinningData.InverseBindPose.clear();
      modelMesh.skinningData.BindPose.clear();
      modelMesh.skinningData.BoneOffset.clear();
      modelMesh.skinningData.BoneIndices.clear();
      modelMesh.skinningData.SkeletonHierarchy.clear();
      modelMesh.skinningData = nullptr;
    }

    if (this.skeleton != nullptr) {
      ImportedSkeleton importedSkeleton = this.skeleton;
      std::unordered_map hashMap = importedSkeleton.clips;
      if (skinningData != nullptr) {
        importedSkeleton.clips.clear();
        hashMap = skinningData.AnimationClips;
      }

      JAssImpImporter.replaceHashMapKeys(importedSkeleton.boneIndices,
                                         "SkinningData.boneIndices");
      modelMesh.skinningData = new SkinningData(
          hashMap, importedSkeleton.bindPose, importedSkeleton.invBindPose,
          importedSkeleton.skinOffsetMatrices,
          importedSkeleton.SkeletonHierarchy, importedSkeleton.boneIndices);
    }

    if (this.skinnedMesh != nullptr && !ModelManager.NoOpenGL) {
      modelMesh.m_bHasVBO = true;
      VertexBufferObject.VertexArray vertexArray1 = this.skinnedMesh.vertices;
      int[] ints1 = this.skinnedMesh.elements;
      RenderThread.queueInvokeOnRenderContext(()->{
        modelMesh.SetVertexBuffer(
            new VertexBufferObject(vertexArray1, ints1, boolean0));
        if (ModelManager.instance.bCreateSoftwareMeshes) {
          modelMesh.softwareMesh.vb = modelMesh.vb;
        }
      });
    }

    this.skeleton = nullptr;
    this.skinnedMesh = nullptr;
    this.staticMesh = nullptr;
  }

  void applyToAnimation(AnimationAsset animationAsset) {
    for (Entry entry : this.skeleton.clips.entrySet()) {
      for (Keyframe keyframe :
           ((AnimationClip)entry.getValue()).getKeyframes()) {
        keyframe.BoneName = JAssImpImporter.getSharedString(
            keyframe.BoneName, "Keyframe.BoneName");
      }
    }

    animationAsset.AnimationClips = this.skeleton.clips;
    this.skeleton = nullptr;
  }
}
} // namespace jassimp
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
