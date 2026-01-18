#pragma once
#include "jassimp/AiPostProcessSteps.h"
#include "jassimp/AiScene.h"
#include "jassimp/Jassimp.h"
#include "org/lwjgl/util/vector/Quaternion.h"
#include "org/lwjgl/util/vector/Vector4f.h"
#include "zombie/core/skinnedmodel/model/jassimp/JAssImpImporter.h"
#include "zombie/core/skinnedmodel/model/jassimp/ProcessedAiScene.h"
#include "zombie/core/skinnedmodel/model/jassimp/ProcessedAiSceneParams.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/fileSystem/FileSystem.h"
#include "zombie/fileSystem/IFileTaskCallback.h"
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class FileTask_LoadMesh : public FileTask_AbstractLoadModel {
public:
  ModelMesh mesh;

public
  FileTask_LoadMesh(ModelMesh modelMesh, FileSystem fileSystem,
                    IFileTaskCallback iFileTaskCallback) {
    super(fileSystem, iFileTaskCallback, "media/models", "media/models_x");
    this.mesh = modelMesh;
  }

  std::string getErrorMessage() { return this.m_fileName; }

  void done() {
    MeshAssetManager.instance.addWatchedFile(this.m_fileName);
    this.mesh.m_fullPath = this.m_fileName;
    this.m_fileName = nullptr;
    this.mesh = nullptr;
  }

  std::string getRawFileName() {
    std::string string = this.mesh.getPath().getPath();
    int int0 = string.indexOf(124);
    return int0 != -1 ? string.substring(0, int0) : string;
  }

  std::string getMeshName() {
    std::string string = this.mesh.getPath().getPath();
    int int0 = string.indexOf(124);
    return int0 != -1 ? string.substring(int0 + 1) : nullptr;
  }

  ProcessedAiScene loadX() {
    EnumSet enumSet = EnumSet.of(
        AiPostProcessSteps.FIND_INSTANCES, AiPostProcessSteps.MAKE_LEFT_HANDED,
        AiPostProcessSteps.LIMIT_BONE_WEIGHTS, AiPostProcessSteps.TRIANGULATE,
        AiPostProcessSteps.OPTIMIZE_MESHES,
        AiPostProcessSteps.REMOVE_REDUNDANT_MATERIALS,
        AiPostProcessSteps.JOIN_IDENTICAL_VERTICES);
    AiScene aiScene = Jassimp.importFile(this.m_fileName, enumSet);
    JAssImpImporter.LoadMode loadMode =
        this.mesh.assetParams.bStatic ? JAssImpImporter.LoadMode.StaticMesh
                                      : JAssImpImporter.LoadMode.Normal;
    ModelMesh modelMesh = this.mesh.assetParams.animationsMesh;
    SkinningData skinningData =
        modelMesh == null ? null : modelMesh.skinningData;
    ProcessedAiSceneParams processedAiSceneParams =
        ProcessedAiSceneParams.create();
    processedAiSceneParams.scene = aiScene;
    processedAiSceneParams.mode = loadMode;
    processedAiSceneParams.skinnedTo = skinningData;
    processedAiSceneParams.meshName = this.getMeshName();
    ProcessedAiScene processedAiScene =
        ProcessedAiScene.process(processedAiSceneParams);
    JAssImpImporter.takeOutTheTrash(aiScene);
    return processedAiScene;
  }

  ProcessedAiScene loadFBX() {
    DebugLog.Animation.debugln("Loading: %s", this.m_fileName);
    EnumSet enumSet = EnumSet.of(
        AiPostProcessSteps.FIND_INSTANCES, AiPostProcessSteps.MAKE_LEFT_HANDED,
        AiPostProcessSteps.LIMIT_BONE_WEIGHTS, AiPostProcessSteps.TRIANGULATE,
        AiPostProcessSteps.OPTIMIZE_MESHES,
        AiPostProcessSteps.REMOVE_REDUNDANT_MATERIALS,
        AiPostProcessSteps.JOIN_IDENTICAL_VERTICES);
    AiScene aiScene = Jassimp.importFile(this.m_fileName, enumSet);
    JAssImpImporter.LoadMode loadMode =
        this.mesh.assetParams.bStatic ? JAssImpImporter.LoadMode.StaticMesh
                                      : JAssImpImporter.LoadMode.Normal;
    ModelMesh modelMesh = this.mesh.assetParams.animationsMesh;
    SkinningData skinningData =
        modelMesh == null ? null : modelMesh.skinningData;
    Quaternion quaternion = new Quaternion();
    Vector4f vector4f = new Vector4f(1.0F, 0.0F, 0.0F, (float)(-Math.PI / 2));
    quaternion.setFromAxisAngle(vector4f);
    ProcessedAiSceneParams processedAiSceneParams =
        ProcessedAiSceneParams.create();
    processedAiSceneParams.scene = aiScene;
    processedAiSceneParams.mode = loadMode;
    processedAiSceneParams.skinnedTo = skinningData;
    processedAiSceneParams.meshName = this.getMeshName();
    processedAiSceneParams.animBonesScaleModifier = 0.01F;
    processedAiSceneParams.animBonesRotateModifier = quaternion;
    ProcessedAiScene processedAiScene =
        ProcessedAiScene.process(processedAiSceneParams);
    JAssImpImporter.takeOutTheTrash(aiScene);
    return processedAiScene;
  }

  ModelTxt loadTxt() {
    bool boolean0 = this.mesh.assetParams.bStatic;
    bool boolean1 = false;
    ModelMesh modelMesh = this.mesh.assetParams.animationsMesh;
    SkinningData skinningData =
        modelMesh == null ? null : modelMesh.skinningData;
    return ModelLoader.instance.loadTxt(this.m_fileName, boolean0, boolean1,
                                        skinningData);
  }

  static enum LoadMode { Assimp, Txt, Missing; }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
