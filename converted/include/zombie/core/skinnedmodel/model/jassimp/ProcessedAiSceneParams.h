#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "jassimp/AiScene.h"
#include "org/lwjgl/util/vector/Quaternion.h"
#include "zombie/core/skinnedmodel/model/SkinningData.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {
namespace jassimp {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ProcessedAiSceneParams {
public:
 AiScene scene = nullptr;
 public JAssImpImporter.LoadMode mode = JAssImpImporter.LoadMode.Normal;
 SkinningData skinnedTo = nullptr;
 std::string meshName = nullptr;
 float animBonesScaleModifier = 1.0F;
 Quaternion animBonesRotateModifier = nullptr;

 ProcessedAiSceneParams() {
 }

 static ProcessedAiSceneParams create() {
 return std::make_unique<ProcessedAiSceneParams>();
 }

 void set(ProcessedAiSceneParams processedAiSceneParams0) {
 this->scene = processedAiSceneParams0.scene;
 this->mode = processedAiSceneParams0.mode;
 this->skinnedTo = processedAiSceneParams0.skinnedTo;
 this->meshName = processedAiSceneParams0.meshName;
 this->animBonesScaleModifier = processedAiSceneParams0.animBonesScaleModifier;
 this->animBonesRotateModifier = processedAiSceneParams0.animBonesRotateModifier;
 }
}
} // namespace jassimp
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
