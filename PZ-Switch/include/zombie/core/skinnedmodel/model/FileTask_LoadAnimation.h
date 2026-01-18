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

class FileTask_LoadAnimation : public FileTask_AbstractLoadModel {
public:
 AnimationAsset m_anim;

public
 FileTask_LoadAnimation(AnimationAsset animationAsset, FileSystem fileSystem,
 IFileTaskCallback iFileTaskCallback) {
 super(fileSystem, iFileTaskCallback, "media/anims", "media/anims_x");
 this->m_anim = animationAsset;
 }

 std::string getRawFileName() { return this->m_anim.getPath().getPath(); }

 std::string getErrorMessage() { return this->m_fileName; }

 void done() {}

 ProcessedAiScene loadX() {
 DebugLog.Animation.debugln("Loading: %s", this->m_fileName);
 EnumSet enumSet = EnumSet.of(AiPostProcessSteps.MAKE_LEFT_HANDED,
 AiPostProcessSteps.REMOVE_REDUNDANT_MATERIALS);
 AiScene aiScene = Jassimp.importFile(this->m_fileName, enumSet);
 JAssImpImporter.LoadMode loadMode = JAssImpImporter.LoadMode.AnimationOnly;
 ModelMesh modelMesh = this->m_anim.assetParams.animationsMesh;
 SkinningData skinningData =
 modelMesh == nullptr ? nullptr : modelMesh.skinningData;
 ProcessedAiSceneParams processedAiSceneParams =
 ProcessedAiSceneParams.create();
 processedAiSceneParams.scene = aiScene;
 processedAiSceneParams.mode = loadMode;
 processedAiSceneParams.skinnedTo = skinningData;
 ProcessedAiScene processedAiScene =
 ProcessedAiScene.process(processedAiSceneParams);
 JAssImpImporter.takeOutTheTrash(aiScene);
 return processedAiScene;
 }

 ProcessedAiScene loadFBX() {
 DebugLog.Animation.debugln("Loading: %s", this->m_fileName);
 EnumSet enumSet = EnumSet.of(AiPostProcessSteps.MAKE_LEFT_HANDED,
 AiPostProcessSteps.REMOVE_REDUNDANT_MATERIALS);
 AiScene aiScene = Jassimp.importFile(this->m_fileName, enumSet);
 JAssImpImporter.LoadMode loadMode = JAssImpImporter.LoadMode.AnimationOnly;
 ModelMesh modelMesh = this->m_anim.assetParams.animationsMesh;
 SkinningData skinningData =
 modelMesh == nullptr ? nullptr : modelMesh.skinningData;
 Quaternion quaternion = new Quaternion();
 Vector4f vector4f = new Vector4f(1.0F, 0.0F, 0.0F, (float)(-Math.PI / 2);
 quaternion.setFromAxisAngle(vector4f);
 ProcessedAiSceneParams processedAiSceneParams =
 ProcessedAiSceneParams.create();
 processedAiSceneParams.scene = aiScene;
 processedAiSceneParams.mode = loadMode;
 processedAiSceneParams.skinnedTo = skinningData;
 processedAiSceneParams.animBonesScaleModifier = 0.01F;
 processedAiSceneParams.animBonesRotateModifier = quaternion;
 ProcessedAiScene processedAiScene =
 ProcessedAiScene.process(processedAiSceneParams);
 JAssImpImporter.takeOutTheTrash(aiScene);
 return processedAiScene;
 }

 ModelTxt loadTxt() {
 bool boolean0 = false;
 bool boolean1 = false;
 ModelMesh modelMesh = this->m_anim.assetParams.animationsMesh;
 SkinningData skinningData =
 modelMesh == nullptr ? nullptr : modelMesh.skinningData;
 return ModelLoader.instance.loadTxt(this->m_fileName, boolean0, boolean1,
 skinningData);
 }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
