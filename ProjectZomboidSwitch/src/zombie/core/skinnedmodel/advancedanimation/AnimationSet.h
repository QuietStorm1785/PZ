#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ZomboidFileSystem.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {


class AnimationSet {
public:
   protected static const std::unordered_map<std::string, AnimationSet> setMap = std::make_unique<std::unordered_map<>>();
   public const std::unordered_map<std::string, AnimState> states = std::make_unique<std::unordered_map<>>();
    std::string m_Name = "";

    static AnimationSet GetAnimationSet(const std::string& var0, bool var1) {
    AnimationSet var2 = setMap.get(var0);
      if (var2 != nullptr && !var1) {
    return var2;
      } else {
         var2 = std::make_unique<AnimationSet>();
         var2.Load(var0);
         setMap.put(var0, var2);
    return var2;
      }
   }

    static void Reset() {
      for (AnimationSet var1 : setMap.values()) {
         var1.clear();
      }

      setMap.clear();
   }

    AnimState GetState(const std::string& var1) {
    AnimState var2 = this.states.get(var1.toLowerCase(Locale.ENGLISH));
      if (var2 != nullptr) {
    return var2;
      } else {
         DebugLog.Animation.warn("AnimState not found: " + var1);
         return std::make_unique<AnimState>();
      }
   }

    bool containsState(const std::string& var1) {
      return this.states.containsKey(var1.toLowerCase(Locale.ENGLISH));
   }

    bool Load(const std::string& var1) {
      if (DebugLog.isEnabled(DebugType.Animation)) {
         DebugLog.Animation.println("Loading AnimSet: " + var1);
      }

      this.m_Name = var1;
      std::string[] var2 = ZomboidFileSystem.instance.resolveAllDirectories("media/AnimSets/" + var1, var0 -> true, false);

    for (auto& var6 : var2)    std::string var7 = std::make_shared<File>(var6).getName();
    AnimState var8 = AnimState.Parse(var7, var6);
         var8.m_Set = this;
         this.states.put(var7, var8);
      }

    return true;
   }

    void clear() {
      for (AnimState var2 : this.states.values()) {
         var2.clear();
      }

      this.states.clear();
   }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
