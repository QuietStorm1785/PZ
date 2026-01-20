#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ZomboidFileSystem.h"
#include "zombie/asset/AssetPath.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/debug/DebugType.h"
#include "zombie/util/StringUtils.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {


class AnimState {
public:
    std::string m_Name = "";
   public const List<AnimNode> m_Nodes = std::make_unique<std::vector<>>();
    int m_DefaultIndex = 0;
    AnimationSet m_Set = nullptr;
    static const bool s_bDebugLog_NodeConditions = false;

   public List<AnimNode> getAnimNodes(IAnimationVariableSource var1, List<AnimNode> var2) {
      var2.clear();
      if (this.m_Nodes.size() <= 0) {
    return var2;
      } else if (DebugOptions.instance.Animation.AnimLayer.AllowAnimNodeOverride.getValue()
         && var1.getVariableBoolean("dbgForceAnim")
         && var1.isVariable("dbgForceAnimStateName", this.m_Name)) {
    std::string var7 = var1.getVariableString("dbgForceAnimNodeName");
    int var8 = 0;

         for (int var9 = this.m_Nodes.size(); var8 < var9; var8++) {
    AnimNode var10 = this.m_Nodes.get(var8);
            if (StringUtils.equalsIgnoreCase(var10.m_Name, var7)) {
               var2.push_back(var10);
               break;
            }
         }

    return var2;
      } else {
    int var3 = -1;
    int var4 = 0;

         for (int var5 = this.m_Nodes.size(); var4 < var5; var4++) {
    AnimNode var6 = this.m_Nodes.get(var4);
            if (!var6.isAbstract() && var6.m_Conditions.size() >= var3 && var6.checkConditions(var1)) {
               if (var3 < var6.m_Conditions.size()) {
                  var2.clear();
                  var3 = var6.m_Conditions.size();
               }

               var2.push_back(var6);
            }
         }

         if (!var2.empty()) {
         }

    return var2;
      }
   }

    static AnimState Parse(const std::string& var0, const std::string& var1) {
    bool var2 = DebugLog.isEnabled(DebugType.Animation);
    AnimState var3 = std::make_shared<AnimState>();
      var3.m_Name = var0;
      if (var2) {
         DebugLog.Animation.println("Loading AnimState: " + var0);
      }

      std::string[] var4 = ZomboidFileSystem.instance.resolveAllFiles(var1, var0x -> var0x.getName().endsWith(".xml"), true);

    for (auto& var8 : var4)    File var9 = std::make_shared<File>(var8);
    std::string var10 = var9.getName().split(".xml")[0].toLowerCase();
         if (var2) {
            DebugLog.Animation.println(var0 + " -> AnimNode: " + var10);
         }

    std::string var11 = ZomboidFileSystem.instance.resolveFileOrGUID(var8);
    AnimNodeAsset var12 = (AnimNodeAsset)AnimNodeAssetManager.instance.load(std::make_shared<AssetPath>(var11));
         if (var12.isReady()) {
    AnimNode var13 = var12.m_animNode;
            var13.m_State = var3;
            var3.m_Nodes.push_back(var13);
         }
      }

    return var3;
   }

    std::string toString() {
      return "AnimState{" + this.m_Name + ", NodeCount:" + this.m_Nodes.size() + ", DefaultIndex:" + this.m_DefaultIndex + "}";
   }

    static std::string getStateName(AnimState var0) {
      return var0 != nullptr ? var0.m_Name : nullptr;
   }

    void clear() {
      this.m_Nodes.clear();
      this.m_Set = nullptr;
   }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
