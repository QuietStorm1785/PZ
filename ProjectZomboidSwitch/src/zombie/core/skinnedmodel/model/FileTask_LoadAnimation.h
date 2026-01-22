#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "jassimp/AiPostProcessSteps.h"
#include "jassimp/AiScene.h"
#include "jassimp/Jassimp.h"
#include "org/lwjgl/util/vector/Quaternion.h"
#include "org/lwjgl/util/vector/Vector4f.h"
#include "zombie/core/skinnedmodel/model/jassimp/JAssImpImporter.h"
#include "zombie/core/skinnedmodel/model/jassimp/JAssImpImporter/LoadMode.h"
#include "zombie/core/skinnedmodel/model/jassimp/ProcessedAiScene.h"
#include "zombie/core/skinnedmodel/model/jassimp/ProcessedAiSceneParams.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/fileSystem/FileSystem.h"
#include "zombie/fileSystem/IFileTaskCallback.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {


class FileTask_LoadAnimation : public FileTask_AbstractLoadModel {
public:
    AnimationAsset m_anim;

    public FileTask_LoadAnimation(AnimationAsset var1, FileSystem var2, IFileTaskCallback var3) {
      super(var2, var3, "media/anims", "media/anims_x");
      this.m_anim = var1;
   }

    std::string getRawFileName() {
      return this.m_anim.getPath().getPath();
   }

    std::string getErrorMessage() {
      return this.m_fileName;
   }

    void done() {
   }

    ProcessedAiScene loadX() {
      DebugLog.Animation.debugln("Loading: %s", this.m_fileName);
    EnumSet var1 = EnumSet.of(AiPostProcessSteps.MAKE_LEFT_HANDED, AiPostProcessSteps.REMOVE_REDUNDANT_MATERIALS);
    AiScene var2 = Jassimp.importFile(this.m_fileName, var1);
    LoadMode var3 = LoadMode.AnimationOnly;
    ModelMesh var4 = this.m_anim.assetParams.animationsMesh;
    SkinningData var5 = var4 == nullptr ? nullptr : var4.skinningData;
    ProcessedAiSceneParams var6 = ProcessedAiSceneParams.create();
      var6.scene = var2;
      var6.mode = var3;
      var6.skinnedTo = var5;
    ProcessedAiScene var7 = ProcessedAiScene.process(var6);
      JAssImpImporter.takeOutTheTrash(var2);
    return var7;
   }

    ProcessedAiScene loadFBX() {
      DebugLog.Animation.debugln("Loading: %s", this.m_fileName);
    EnumSet var1 = EnumSet.of(AiPostProcessSteps.MAKE_LEFT_HANDED, AiPostProcessSteps.REMOVE_REDUNDANT_MATERIALS);
    AiScene var2 = Jassimp.importFile(this.m_fileName, var1);
    LoadMode var3 = LoadMode.AnimationOnly;
    ModelMesh var4 = this.m_anim.assetParams.animationsMesh;
    SkinningData var5 = var4 == nullptr ? nullptr : var4.skinningData;
    Quaternion var6 = std::make_shared<Quaternion>();
    Vector4f var7 = std::make_shared<Vector4f>(1.0F, 0.0F, 0.0F, (float) (-Math.PI / 2));
      var6.setFromAxisAngle(var7);
    ProcessedAiSceneParams var8 = ProcessedAiSceneParams.create();
      var8.scene = var2;
      var8.mode = var3;
      var8.skinnedTo = var5;
      var8.animBonesScaleModifier = 0.01F;
      var8.animBonesRotateModifier = var6;
    ProcessedAiScene var9 = ProcessedAiScene.process(var8);
      JAssImpImporter.takeOutTheTrash(var2);
    return var9;
   }

    ModelTxt loadTxt() {
    bool var1 = false;
    bool var2 = false;
    ModelMesh var3 = this.m_anim.assetParams.animationsMesh;
    SkinningData var4 = var3 == nullptr ? nullptr : var3.skinningData;
      return ModelLoader.instance.loadTxt(this.m_fileName, var1, var2, var4);
   }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
