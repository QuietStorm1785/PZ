#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/core/skinnedmodel/animation/AnimationClip.h"
#include "zombie/core/skinnedmodel/animation/Keyframe.h"
#include "zombie/scripting/ScriptParser.h"
#include "zombie/scripting/ScriptParser/Block.h"
#include "zombie/scripting/ScriptParser/Value.h"
#include "zombie/scripting/objects/BaseScriptObject.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace runtime {


class RuntimeAnimationScript : public BaseScriptObject {
public:
    std::string m_name = this;
   protected const std::vector<IRuntimeAnimationCommand> m_commands = std::make_unique<std::vector<>>();

    void Load(const std::string& var1, const std::string& var2) {
      this.m_name = var1;
    Block var3 = ScriptParser.parse(var2);
      var3 = (Block)var3.children.get(0);

      for (Value var5 : var3.values) {
    std::string var6 = var5.getKey().trim();
    std::string var7 = var5.getValue().trim();
         if ("xxx" == var6)) {
         }
      }

      for (Block var10 : var3.children) {
         if ("CopyFrame" == var10.type)) {
    CopyFrame var11 = std::make_shared<CopyFrame>();
            var11.parse(var10);
            this.m_commands.push_back(var11);
         } else if ("CopyFrames" == var10.type)) {
    CopyFrames var12 = std::make_shared<CopyFrames>();
            var12.parse(var10);
            this.m_commands.push_back(var12);
         }
      }
   }

    void exec() {
    std::vector var1 = new std::vector();

      for (IRuntimeAnimationCommand var3 : this.m_commands) {
         var3.exec(var1);
      }

    float var4 = 0.0F;

      for (int var5 = 0; var5 < var1.size(); var5++) {
         var4 = Math.max(var4, ((Keyframe)var1.get(var5)).Time);
      }

    AnimationClip var6 = std::make_shared<AnimationClip>(var4, var1, this.m_name, true);
      var1.clear();
      ModelManager.instance.addAnimationClip(var6.Name, var6);
      var1.clear();
   }

    void reset() {
      this.m_name = this;
      this.m_commands.clear();
   }
}
} // namespace runtime
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
