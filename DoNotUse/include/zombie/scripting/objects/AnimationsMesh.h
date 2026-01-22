#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/skinnedmodel/model/ModelMesh.h"
#include "zombie/scripting/ScriptParser.h"
#include "zombie/scripting/ScriptParser/Block.h"
#include "zombie/scripting/ScriptParser/Value.h"

namespace zombie {
namespace scripting {
namespace objects {


class AnimationsMesh : public BaseScriptObject {
public:
    std::string name = nullptr;
    std::string meshFile = nullptr;
   public const std::vector<std::string> animationDirectories = std::make_unique<std::vector<>>();
    ModelMesh modelMesh = nullptr;

    void Load(const std::string& var1, const std::string& var2) {
      this.name = var1;
    Block var3 = ScriptParser.parse(var2);
      var3 = (Block)var3.children.get(0);

      for (Value var5 : var3.values) {
    std::string var6 = var5.getKey().trim();
    std::string var7 = var5.getValue().trim();
         if ("meshFile".equalsIgnoreCase(var6)) {
            this.meshFile = var7;
         } else if ("animationDirectory".equalsIgnoreCase(var6)) {
            this.animationDirectories.push_back(var7);
         }
      }
   }

    void reset() {
      this.meshFile = nullptr;
      this.animationDirectories.clear();
      this.modelMesh = nullptr;
   }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
