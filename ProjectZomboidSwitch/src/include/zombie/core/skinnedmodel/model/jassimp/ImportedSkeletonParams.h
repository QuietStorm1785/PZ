#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "jassimp/AiMesh.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {
namespace jassimp {


class ImportedSkeletonParams : public ProcessedAiSceneParams {
public:
    AiMesh mesh = nullptr;

   ImportedSkeletonParams() {
   }

    static ImportedSkeletonParams create(ProcessedAiSceneParams var0, AiMesh var1) {
    ImportedSkeletonParams var2 = std::make_shared<ImportedSkeletonParams>();
      var2.set(var0);
      var2.mesh = var1;
    return var2;
   }
}
} // namespace jassimp
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
