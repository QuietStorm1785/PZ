#pragma once
#include "jassimp/AiMesh.h"
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

class ImportedSkeletonParams : public ProcessedAiSceneParams {
public:
  AiMesh mesh = nullptr;

  ImportedSkeletonParams() {}

  static ImportedSkeletonParams
  create(ProcessedAiSceneParams processedAiSceneParams, AiMesh aiMesh) {
    ImportedSkeletonParams importedSkeletonParams =
        new ImportedSkeletonParams();
    importedSkeletonParams.set(processedAiSceneParams);
    importedSkeletonParams.mesh = aiMesh;
    return importedSkeletonParams;
  }
}
} // namespace jassimp
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
